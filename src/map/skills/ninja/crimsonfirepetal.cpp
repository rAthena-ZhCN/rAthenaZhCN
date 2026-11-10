// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "crimsonfirepetal.hpp"

#include "map/map.hpp"
#include "map/pc.hpp"

SkillCrimsonFirePetal::SkillCrimsonFirePetal() : SkillImpl(NJ_KOUENKA) {
}

void SkillCrimsonFirePetal::calculateSkillRatio(const Damage *wd, const block_list *src, const block_list *target, uint16 skill_lv, int32 &base_skillratio, int32 mflag) const {
	const map_session_data* sd = BL_CAST(BL_PC, src);

	base_skillratio -= 10;
	if(sd && sd->spiritcharm_type == CHARM_TYPE_FIRE && sd->spiritcharm > 0)
		base_skillratio += 10 * sd->spiritcharm;
}

void SkillCrimsonFirePetal::castendDamageId(block_list *src, block_list *target, uint16 skill_lv, t_tick tick, int32& flag) const {
	status_change *sc = status_get_sc(src);

	if (flag & 1) {
		skill_attack(BF_MAGIC, src, src, target, getSkillId(), skill_lv, tick, flag);
		return;
	}
	if (sc != nullptr && sc->getSCE(SC_HERO_SOUL)) {
		// Ninja Hero Soul: 5x5 splash around the target.
		map_foreachinrange(skill_area_sub, target, 2, BL_CHAR, src, getSkillId(), skill_lv, tick, flag | BCT_ENEMY | SD_SPLASH | 1, skill_castend_damage_id);
		return;
	}
	skill_attack(BF_MAGIC, src, src, target, getSkillId(), skill_lv, tick, flag);
}
