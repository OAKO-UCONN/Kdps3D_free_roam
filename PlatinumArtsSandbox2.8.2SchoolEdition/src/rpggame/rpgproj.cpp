#include "rpggame.h"

VARP(firemethod, 0, 1, 1);
VARP(friendlyfire, 0, 0, 1);

void projectile::init(rpgchar *d, equipment *w, equipment *a, int fuzzy, float mult, float speed)
{
	if(DEBUG_PROJ)
		conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr Creating projectile; Owner %p item %p fuzzy %i mult %f speed %f ...", d, w, fuzzy, mult, speed);

	dir = vec(RAD * d->yaw, RAD * d->pitch);
	if(fuzzy > 0)
	{
		vec axis(rnd(360) * RAD, rnd(360) * RAD);
		dir.rotate(fuzzy * RAD / 2.f, axis);
	}
	o = d->o;

	//we now need to move the projectile outside the player's bounding box
	vec test = vec(dir).mul(max(d->eyeheight, d->radius) * 4); test.add(o);

	{
		float mult = 0;
		game::intersect(d, test, o, mult);

		mult = (1 - mult ) + 0.0001;
		mult *= test.dist(o);

		//finally move it just outside the bounding box
		o.add(vec(dir).mul(mult));
	}

	//initialise the other stuff
	owner = d;
	emitpos = o;

	if(DEBUG_PROJ)
		conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr owner BB collision point: %f %f %f ...", o.x, o.y, o.z);

	if(w)
	{
		item = *w;
		use_weapon *wep = (use_weapon *) w->it->uses[w->use];

		projfx = wep->projeffect;
		trailfx = wep->traileffect;
		deathfx = wep->deatheffect;
		dist = wep->range;
		time = wep->lifetime;
		pflags = wep->pflags;
		elasticity = wep->elasticity;
		radius = wep->radius;
		speed = wep->speed;
		gravity = wep->gravity;
		chargeflags = wep->chargeflags;

		if(DEBUG_PROJ)
			conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr weapon was provided... fx: %i %i %i dist: %i time: %i pflags: %i elasticity %f radius: %i speed %f gravity: %i", projfx, trailfx, deathfx, dist, time, pflags, elasticity, radius, dir.magnitude(), gravity);
	}
	if(a)
	{
		ammo = *a;
		use_weapon *wep = (use_weapon *) a->it->uses[a->use];

		 //visuals take precedence - if they have them
		if(wep->projeffect >= 0)
			projfx = wep->projeffect;
		if(wep->traileffect >= 0)
			trailfx = wep->traileffect;
		if(wep->deatheffect >= 0)
			deathfx = wep->deatheffect;
		dist += wep->range;
		time += wep->lifetime;
		pflags |= wep->pflags;
		elasticity = max(elasticity, wep->elasticity);
		radius += wep->radius;
		speed += wep->speed;
		gravity += wep->gravity; // let the implement modulate gravity
		chargeflags |= wep->chargeflags;

		if(DEBUG_PROJ)
			conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr ammo was provided... fx: %i %i %i dist: %i time: %i pflags: %i elasticity %f radius: %i speed: %f gravity: %i", projfx, trailfx, deathfx, dist, time, pflags, elasticity, radius, dir.magnitude(), gravity);
	}
	radius = max(1, radius);
	dir.mul(speed);

	if(chargeflags & CHARGE_SPEED) dir.mul(mult);
	if(chargeflags & CHARGE_TRAVEL) {dist *= mult; time *= mult;}
	if(chargeflags & CHARGE_RADIUS) radius *= mult;
	charge = mult;
	if(DEBUG_PROJ) conoutf("\fs\f2DEBUG:\fr applied charge flags; speed %f dist %i time %i radius %i", dir.magnitude(), dist, time, radius);

	if(firemethod || d != game::player1)
	{ //add the actor's velocity, but adjust for it so it doesn't deviate from the intended target
		vec vel(d->vel);
		vel.add(d->falling);
		vel.div(100.0f);
		vel.add(dir);

		dir.normalize();
		dir.mul(vel.magnitude());

		if(DEBUG_PROJ)
			conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr compensating for owner velocity, dir: (%f, %f, %f) speed: %f", dir.x, dir.y, dir.z, dir.magnitude());
	}
	else
	{
		//just add the actor's velocity, no adjusting
		vec vel(d->vel);
		vel.add(d->falling);
		vel.div(100.0f);
		dir.add(vel);

		if(DEBUG_PROJ)
			conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr adding owner velocity, dir: (%f, %f, %f) speed: %f", dir.x, dir.y, dir.z, dir.magnitude());
	}
}

VARP(maxricochets, 1, 5, 100);
vec normal;

bool projectile::update()
{
	if(deleted) return false;

	vector<rpgent *> victims;
	if(pflags & P_TIME) time -= curtime;

	if(! (pflags & P_STATIONARY))
	{
		float vel = 100.0f * dir.magnitude();
		float distance = vel * curtime / 1000.0f;
		int tries = 0;

		while(!deleted && distance > 0 && tries < maxricochets)
		{
			++tries;
			float offset = travel(distance, victims);

			if((victims.length() && !(pflags & P_PERSIST))) deleted = true;
			else if(distance > 0)
			{
				if(pflags & P_RICOCHET)
				{
					//offset slightly - avoids colliding with the same thing
					o.add(vec(normal).mul(.1));

					//reflect around normal
					//conoutf("bef:  %f %f %f; %f %f %f; %f", dir.x, dir.y, dir.z, normal.x, normal.y, normal.z, dir.dot(normal));
					dir.reflect(normal);
					dir.mul(elasticity);
					dir.z -= gravity * (offset / vel) / 100.f;
					vel = 100.f * dir.magnitude();
					distance *= elasticity;
					//conoutf("aft: %f %f %f; %f %f %f; %f", dir.x, dir.y, dir.z, normal.x, normal.y, normal.z, dir.dot(normal));

					//in relation to the above, a negative dot product means gravity turned it around; freeze it
					if(dir.magnitude() > 1e-6f && (dir.magnitude() > 1e-5f && dir.dot(normal) > -.25))
						continue;
				}

				if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr freezing projectile %p", this);
				if(pflags & P_VOLATILE) deleted = true;
				else if(pflags & P_PROXIMITY) pflags |= P_STATIONARY;
				else pflags |= P_VOLATILE|P_STATIONARY; //expire timers first before exploding - handled below
				break;
			}
			else
				dir.z -= gravity * offset / vel / 100.f;
		}
	}

	if((pflags & (P_STATIONARY|P_PROXIMITY|P_TIME)) == P_STATIONARY)
	{
		if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr projectile %p has no timer - nor \"trap\"; forcing delete due to no victims", this);
		deleted = true;
	}

	if(o.x < 0 || o.x >= getworldsize() ||
	   o.y < 0 || o.y >= getworldsize() ||
	   o.z < 0 || o.z >= getworldsize()
	)
	{
		if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr projectile %p out of world - deleting", this);
		pflags &= ~P_VOLATILE;
		deleted = true;
	}

	if((pflags & P_TIME && time <= 0) || (pflags & P_DIST && dist <= 0))
	{
		if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr projectile %p; timers expired", this);
		deleted = true;
	}

	if(pflags & P_PROXIMITY)
	{
		loopv(game::curmap->objs)
		{
			rpgent *d = game::curmap->objs[i];
			if(d != owner && radius >= o.dist_to_bb(d->feetpos(), d->o) - d->radius)
				victims.add(d);
		}
	}

	use_weapon *wep = (use_weapon *) (item.it ? item.it->uses[item.use] : NULL);
	use_weapon *amm = (use_weapon *) (ammo.it ? ammo.it->uses[ammo.use] : NULL);

	if(victims.length())
	{
		if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr projectile %p has victims - hit/bounced of/pierced; applying damage?", this);
		if(!(pflags & P_PERSIST)) deleted = true;

		if(wep) loopv(victims)
		{
			if(hits.find(victims[i]) == -1)
			{
				hits.add(victims[i]);
				victims[i]->hit(owner, wep, amm, charge, chargeflags, dir);
			}
		}
	}

	if(deleted)
	{
		if(victims.length() || pflags & P_VOLATILE) drawdeath();

		if(!wep) return true;

		//see if the used ammo is retained after use
		if(wep->ammo >= 0 &&
			o.x >= 0 && o.x < getworldsize() &&
			o.y >= 0 && o.y < getworldsize() &&
			o.z >= 0 && o.z < getworldsize()
		)
		{
			int retain = 0;
			loopi(wep->cost) if((amm ? ammo : item).it->recovery * 100 > rnd(100))
				retain++;

			if(retain)
			{
				::item *it = (amm ? ammo : item).it;
				int prev = it->quantity;
				it->quantity = retain;

				if(pflags & P_PERSIST || !victims.length() || !victims[0]->additem(it))
				{
					rpgitem *rit = new rpgitem();
					game::curmap->objs.add(rit);
					it->transfer(*rit);

					vectoyawpitch(dir, rit->yaw, rit->pitch);
					rit->resetmdl();
					setbbfrommodel(rit, rit->temp.mdl);
					rit->o = o;
					rit->o.z -= rit->eyeheight / 2;
					dir.rescale(rit->radius);
					rit->o.sub(dir);

					entinmap(rit);
				}

				it->quantity = prev;
			}
		}

		switch(amm ? amm->target : wep->target)
		{
			case T_SINGLE: break; // handled above
			case T_MULTI:
			case T_SMULTI:
				loopv(game::curmap->objs)
				{
					rpgent *d = game::curmap->objs[i];
					if((d != owner || friendlyfire) && hits.find(d) == -1 && radius >= o.dist_to_bb<vec>(d->feetpos(), d->o)  - d->radius)
					{
						vec kick = vec(d->o).sub(o).normalize();
						d->hit(owner, wep, amm, charge, chargeflags, kick);
					}
				}
				break;
			case T_AREA:
			case T_SAREA:
			{
				//TODO status effect specific particle effects
				loopv(wep->effects)
				{
					areaeffect *aeff = game::curmap->aeffects.add(new areaeffect());
					statusgroup *sg = game::statuses[wep->effects[i]->status];

					aeff->owner = owner;
					aeff->o = o;
					aeff->radius = radius;

					aeff->fx = wep->deatheffect;
					aeff->group = wep->effects[i]->status;
					aeff->elem = sg->friendly ? ATTACK_NONE : wep->effects[i]->element;

					loopvj(sg->effects)
					{
						status *st = aeff->effects.add(sg->effects[j]->dup());
						st->remain = st->duration;

						if(chargeflags & CHARGE_MAG) st->strength *= charge;
						if(chargeflags & CHARGE_DURATION) st->remain *= charge;
					}

					if(chargeflags & CHARGE_RADIUS) radius *= charge;
				}

				if(amm) loopv(amm->effects)
				{
					areaeffect *aeff = game::curmap->aeffects.add(new areaeffect());
					statusgroup *sg = game::statuses[amm->effects[i]->status];

					aeff->owner = owner;
					aeff->o = o;
					aeff->radius = radius;

					aeff->fx = amm->deatheffect;
					aeff->group = amm->effects[i]->status;
					aeff->elem = sg->friendly ? ATTACK_NONE : amm->effects[i]->element;

					loopvj(sg->effects)
					{
						status *st = aeff->effects.add(sg->effects[j]->dup());
						st->remain = st->duration;

						if(chargeflags & CHARGE_MAG) st->strength *= charge;
						if(chargeflags & CHARGE_DURATION) st->remain *= charge;
					}

					if(chargeflags & CHARGE_RADIUS) radius *= charge;
				}
				break;
			}
		}
	}

	return true;
}

float projectile::travel(float &distance, vector<rpgent *> &victims)
{
	vec pos;
	float geomdist = raycubepos(o, vec(dir).normalize(), pos, distance, RAY_CLIPMAT|RAY_ALPHAPOLY);

	if((pflags & (P_PERSIST|P_RICOCHET)) == P_PERSIST)
	{
		distance -= geomdist;
		if(pflags & P_DIST) dist -= geomdist;

		loopv(game::curmap->objs)
		{
			static float tmp;
			rpgent *vic = game::curmap->objs[i];
			if((vic != owner || friendlyfire) && game::intersect(vic, o, pos, tmp))
			{
				if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr piercing projectile %p, adding victim %p", this, vic);
				victims.add(vic);
			}
		}
		o = pos;
		return geomdist;
	}
	else
	{
		extern vec hitsurface;
		normal = hitsurface;

		float entdist = 0;
		rpgent *vic = game::intersectclosest(o, pos, friendlyfire ? NULL : owner, entdist, 2);
		if(vic && entdist <= 1)
		{
			if(DEBUG_PROJ) conoutf(CON_DEBUG, "\fs\f2DEBUG:\fr projectile %p has victim %p", this, vic);
			victims.add(vic);

			pos.sub(o).mul(entdist).add(o);
			geomdist *= entdist;
			normal = vec(pos).sub(vic->o).normalize();
		}

		o = pos;
		if(pflags & P_DIST) dist -= geomdist;
		distance -= geomdist;
		return geomdist;
	}
}

VARP(projallowflare, 0, 1, 1);

void projectile::render(bool mainpass)
{
	if(game::effects.inrange(projfx))
	{
		effect *e = game::effects[projfx];

		if(e->mdl)
		{
			float yaw, pitch, roll;
			vectoyawpitch(dir, yaw, pitch);
			roll = 0;

			if(!e->spin.iszero())
			{
				if(e->spin.x) yaw += e->spin.x * lastmillis / 50;
				if(e->spin.y) pitch += e->spin.y * lastmillis / 50;
				if(e->spin.z) roll += e->spin.z * lastmillis / 50;
			}

			rendermodel(&light, e->mdl, ANIM_MAPMODEL|ANIM_LOOP, o, yaw + 90, pitch, roll, MDL_SHADOW);
		}
		else if (mainpass)
		{
			e->drawsplash(o, dir, 0, charge, effect::PROJ, 0);
			if(projallowflare && e->flags & (FX_FIXEDFLARE|FX_FLARE))
			{
				vec col = vec(e->lightcol).mul(256);
				bool fixed = e->flags & FX_FIXEDFLARE;
				regularlensflare(o, col.x, col.y, col.z, fixed, false, e->lightradius * (fixed ? .5f : 5.0f));
			}
		}
	}
	if(!(pflags&P_STATIONARY) && mainpass && game::effects.inrange(trailfx) &&
		game::effects[trailfx]->drawline(emitpos, o, 1, effect::TRAIL, lastmillis - lastemit))
		lastemit = lastmillis;
}

void projectile::drawdeath()
{
	if(game::effects.inrange(deathfx))
		game::effects[deathfx]->drawsphere(o, radius, 1, effect::DEATH, 0);
}

void projectile::dynlight()
{
	if(deleted)
	{
		if(!game::effects.inrange(deathfx)) return;
		effect *e = game::effects[deathfx];
		if(!(e->flags & FX_DYNLIGHT)) return;
		adddynlight(o, e->lightradius, e->lightcol, e->lightfade, e->lightfade / 2, e->lightflags, e->lightinitradius, e->lightinitcol);
	}
	else
	{
		if(!game::effects.inrange(projfx)) return;
		effect *e = game::effects[projfx];
		if(!(e->flags & FX_DYNLIGHT)) return;
		adddynlight(o, e->lightradius, e->lightcol);
	}
}
