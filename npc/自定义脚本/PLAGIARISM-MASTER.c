
//=================================================================|
/*|---------------- 脚本信息 SCRIPT INFORMATION---------------------|
  | Name: Plagiarism Master (0x0442 (ZC_SKILL_SELECT_REQUEST)      |
  | 中文翻译：99Max.me[xpa]                                         |
  | Author: [royrdev]                                              |
  | Request: (Hyllok)                                              |
  | Date: [2026.01.23]                                             |
  | Version : 2.0                                                  |
  | Description:                                                   |
  | Plagiarism NPC using the skillselectmenu() UI selection.       |
  | Supports multiple SK categories with configurable skill lists. |
  |                                                                |
  | Important Notes:                                               |
  |                                                                |
  |   plagiarizeskill() checks if the skill has                    |
  |   SKILL_COPY_PLAGIARISM flag in skill_db.yml. If your skills   |
  |   FAIL TO COPY. You need to add the Copyable 'FLAG' to them    |
  |   in db/pre-re or re/skill_db.yml                              |
  |================================================================|
  | Compatible: rAthena Emulator                                   |
  |_______________________________________________________________*/

prontera.gat, 152, 185, 4	script	Plagiarism Master	4_M_YOYOROGUE,{
	if( (Class != Job_Rogue) && (Class != Job_Stalker) ) {
		mes(.npc_name$);
		mes(sprintf("Greetings ^0055FF%s^000000.", strcharinfo(PC_NAME)));
		mes("I am the ^FF0000Plagiarism Master^000000.");
		mes("\n");
		mes("Unfortunately, only <b>^0000FFRogues^000000</b> and <b>^0000FFStalkers^000000</b> can utilize my services.");
		close();
	}
	mes(.npc_name$);
	mes(sprintf("Greetings ^0055FF%s^000000.", strcharinfo(PC_NAME)));
	mes("I am the <b>^FF0000Plagiarism Master^000000</b>.");
	mes("\n");
	mes(sprintf("For %sz, I can help you copy any skill of your choosing.", callfunc("F_InsertComma", .skill_zeny)));
	next();
	.@menu_choice = select(
		"- Acolyte Skills",
		"- Archer Skills",
		"- Mage Skills",
		"- Merchant Skills",
		"- Ninja Skills",
		"- Swordsman Skills",
		"- Taekwon Skills",
		"- Thief Skills",
		"- Miscellaneous Skills",
		"- View Current Plagiarism",
		"- Reset Plagiarism",
		"- Cancel"
	);
	if( .@menu_choice == 10 ) {
		mes(.npc_name$);
		if( getskilllv(getskillid("RG_PLAGIARISM")) > 0 ) {
			.@current_id = getplagiarizedskill(1);
			.@current_lv = getplagiarizedskilllv(1);
			if( .@current_id > 0 ) {
				mes("Your currently <b>Plagiarized </b>skill is:");
				// getskilldesc = Friendly Name (Detect)
				// getskillname = Constant Name (HT_DETECTING)
				mes(sprintf("<b>^0000FF%s^000000</b> (^777777%s^000000) ^00AA00Lv.%d^000000", getskilldesc(.@current_id), getskillname(.@current_id), .@current_lv));
			}
			else {
				mes("You don't have any skill plagiarized yet.");
			}
		}
		else {
			mes("You haven't learned the Plagiarism skill yet.");
		}
		close();
	}
	if( .@menu_choice == 11 ) {
		mes(.npc_name$);
		if( getstatus(SC_PRESERVE) ) {
			mes("You have ^FF0000Preserve^000000 active.");
			mes("I will remove it before resetting your plagiarized skill.");
			next();
			sc_end(SC_PRESERVE);
		}
		plagiarizeskillreset(1);
		mes("Your plagiarized skill has been reset.");
		specialeffect2(EF_REPAIRWEAPON);
		close();
	}
	if( .@menu_choice == 12 ) {
		mes(.npc_name$);
		mes("Please come back anytime you need my services.");
		close();
	}
	// Using Skill Constant Names
	switch (.@menu_choice ) {
		case 1: // Acolyte Skills
			.@category$ = "Acolyte Class";
			setarray(.@skill_names$[0],
				"AL_HEAL",        // Heal
				"AL_INCAGI",      // Increase AGI
				"AL_DECAGI",      // Decrease AGI
				"AL_BLESSING",    // Blessing
				"PR_MAGNIFICAT",  // Magnificat
				"PR_GLORIA",      // Gloria
				"PR_LEXDIVINA",   // Lex Divina
				"PR_TURNUNDEAD",  // Turn Undead
				"HP_ASSUMPTIO",   // Assumptio
				"AB_RENOVATIO"    // Renovatio
			);
			setarray(.@skill_lvs[0], 10, 10, 10, 10, 5, 5, 10, 10, 5, 1);
			break;
		case 2: // Archer Skills
			.@category$ = "Archer Class";
			setarray(.@skill_names$[0],
				"AC_DOUBLE",      // Double Strafe
				"AC_SHOWER",      // Arrow Shower
				"HT_BLITZBEAT",   // Blitz Beat
				"HT_DETECTING",   // Detect
				"HT_SPRINGTRAP",  // Remove Trap
				"HT_PHANTASMIC",  // Phantasmic Arrow
				"SN_FALCONASSAULT" // Falcon Assault
			);
			setarray(.@skill_lvs[0], 10, 10, 5, 4, 1, 5, 5);
			break;
		case 3: // Mage Skills
			.@category$ = "Mage Class";
			setarray(.@skill_names$[0],
				"MG_NAPALMBEAT",   // Napalm Beat
				"MG_SOULSTRIKE",   // Soul Strike
				"MG_COLDBOLT",     // Cold Bolt
				"MG_FIREBOLT",     // Fire Bolt
				"MG_LIGHTNINGBOLT",// Lightning Bolt
				"MG_THUNDERSTORM", // Thunderstorm
				"MG_FIREBALL",     // Fire Ball
				"MG_FIREWALL",     // Fire Wall
				"MG_FROSTDIVER",   // Frost Diver
				"WZ_FIREPILLAR",   // Fire Pillar
				"WZ_METEOR",       // Meteor Storm
				"WZ_JUPITEL",      // Jupitel Thunder
				"WZ_VERMILION",    // Lord of Vermilion
				"WZ_STORMGUST",    // Storm Gust
				"WZ_EARTHSPIKE",   // Earth Spike
				"WZ_HEAVENDRIVE",  // Heaven's Drive
				"HW_NAPALMVULCAN", // Napalm Vulcan
				"HW_GRAVITATION",  // Gravitation Field
				"PF_SOULBURN"      // Soul Burn
			);
			setarray(.@skill_lvs[0], 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 5, 5, 5, 5);
			break;
		case 4: // Merchant Skills
			.@category$ = "Merchant Class";
			setarray(.@skill_names$[0],
				"MC_MAMMONITE",    // Mammonite
				"BS_HAMMERFALL",   // Hammer Fall
				"WS_CARTTERMINATION" // Cart Termination
			);
			setarray(.@skill_lvs[0], 10, 5, 10);
			break;
		case 5: // Ninja Skills
			.@category$ = "Ninja Class";
			setarray(.@skill_names$[0],
				"NJ_TOBIDOUGU",    // Throw Shuriken
				"NJ_SYURIKEN",     // Throw Kunai
				"NJ_HUUMA",        // Throw Huuma Shuriken
				"NJ_KOUENKA",      // Crimson Fire Petal
				"NJ_KAENSIN",      // Crimson Fire Formation
				"NJ_BAKUENRYU",    // Dragon Fire Formation
				"NJ_HYOUSENSOU",   // Freezing Spear
				"NJ_SUITON",       // Water Escape
				"NJ_HYOUSYOURAKU", // Falling Ice Pillar
				"NJ_HUUJIN",       // Wind Blade
				"NJ_RAIGEKISAI",   // Lightning Strike
				"NJ_KAMAITACHI",   // Wind Slasher
				"NJ_ISSEN",        // Final Strike
				"NJ_KIRIKAGE"      // Shadow Slash
			);
			setarray(.@skill_lvs[0], 10, 5, 5, 10, 10, 5, 10, 10, 5, 10, 5, 10, 10, 5);
			break;
		case 6: // Swordsman Skills
			.@category$ = "Swordsman Class";
			setarray(.@skill_names$[0],
				"SM_BASH",         // Bash
				"SM_MAGNUM",       // Magnum Break
				"KN_BOWLINGBASH",  // Bowling Bash
				"KN_BRANDISHSPEAR",// Brandish Spear
				"KN_SPEARBOOMERANG",// Spear Boomerang
				"LK_SPIRALPIERCE", // Spiral Pierce
				"LK_HEADCRUSH",    // Head Crush
				"LK_JOINTBEAT",    // Joint Beat
				"RK_HUNDREDSPEAR", // Hundred Spears
				"RK_WINDCUTTER"    // Wind Cutter
			);
			setarray(.@skill_lvs[0], 10, 10, 10, 10, 5, 5, 5, 10, 10, 5);
			break;
		case 7: // Taekwon Skills
			.@category$ = "Taekwon Class";
			setarray(.@skill_names$[0],
				"TK_STORMKICK",    // Storm Kick
				"TK_DOWNKICK",     // Down Kick
				"TK_TURNKICK",     // Turn Kick
				"TK_COUNTER",      // Counter
				"TK_JUMPKICK"      // Flying Side Kick
			);
			setarray(.@skill_lvs[0], 7, 7, 7, 7, 7);
			break;
		case 8: // Thief Skills
			.@category$ = "Thief Class";
			setarray(.@skill_names$[0],
				"TF_POISON",       // Envenom
				"AS_SONICBLOW",    // Sonic Blow
				"AS_GRIMTOOTH",    // Grimtooth
				"AS_VENOMDUST",    // Venom Dust
				"AS_SPLASHER",     // Venom Splasher
				"ASC_BREAKER",     // Soul Breaker
				"ASC_METEORASSAULT",// Meteor Assault
				"GC_CROSSIMPACT",  // Cross Impact
				"GC_DARKILLUSION"  // Dark Illusion
			);
			setarray(.@skill_lvs[0], 10, 10, 5, 10, 10, 10, 10, 5, 5);
			break;
		case 9: // Miscellaneous Skills
			.@category$ = "Miscellaneous";
			setarray(.@skill_names$[0],
				"CR_ACIDDEMONSTRATION", // Acid Demonstration
				"CG_ARROWVULCAN",  // Arrow Vulcan
				"SL_SMA"           // Esma
			);
			setarray(.@skill_lvs[0], 10, 10, 10);
			break;
		default:
			mes(.npc_name$);
			mes("Invalid selection.");
			close();
	}
	.@count = getarraysize(.@skill_names$);
	// Convert string names to numeric IDs
	for( .@i = 0; .@i < .@count; ++.@i ) {
		.@skill_ids[.@i] = getskillid(.@skill_names$[.@i]);
	}
	mes(.npc_name$);
	mes(sprintf("<b>^0055FF%s Skills^000000</b>", .@category$));
	mes("Please select a skill from the UI window.");
	mes("\n");
	mes("<b>^FF0000Note:^000000</b> Close the window to cancel.");
	next();
	switch(.@count)
	{ // skillselectmenu() with skill names (Accepts Strings)
		case 1:
			.@selected = skillselectmenu(.@skill_names$[0]);
			break;
		case 2:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1]);
			break;
		case 3:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2]);
			break;
		case 4:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3]);
			break;
		case 5:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4]);
			break;
		case 6:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5]);
			break;
		case 7:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6]);
			break;
		case 8:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7]);
			break;
		case 9:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8]);
			break;
		case 10:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9]);
			break;
		case 11:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10]);
			break;
		case 12:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11]);
			break;
		case 13:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12]);
			break;
		case 14:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13]);
			break;
		case 15:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14]);
			break;
		case 16:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14], .@skill_names$[15]);
			break;
		case 17:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14], .@skill_names$[15], .@skill_names$[16]);
			break;
		case 18:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14], .@skill_names$[15], .@skill_names$[16], .@skill_names$[17]);
			break;
		case 19:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14], .@skill_names$[15], .@skill_names$[16], .@skill_names$[17], .@skill_names$[18]);
			break;
		case 20:
			.@selected = skillselectmenu(.@skill_names$[0], .@skill_names$[1], .@skill_names$[2], .@skill_names$[3], .@skill_names$[4], .@skill_names$[5], .@skill_names$[6], .@skill_names$[7], .@skill_names$[8], .@skill_names$[9], .@skill_names$[10], .@skill_names$[11], .@skill_names$[12], .@skill_names$[13], .@skill_names$[14], .@skill_names$[15], .@skill_names$[16], .@skill_names$[17], .@skill_names$[18], .@skill_names$[19]);
			break;
		default:
			mes(.npc_name$);
			mes("<b>^FF0000Error:^000000</b> Too many skills in this category.");
			close();
	}
	if( (.@selected == 0) || (.@selected == -1) ) {
		clear();
		mes(.npc_name$);
		mes("The <i>Selection UI</i> canceled.");
		mes("Please return whenever you feel prepared.");
		close();
	}
	// Check if player already has this skill plagiarized
	.@current_id = getplagiarizedskill(1);
	if( .@current_id == .@selected ) {
		mes(.npc_name$);
		mes(sprintf("You already have <b>^0000FF%s^000000</b> (^777777%s^000000) Plagiarized.", getskilldesc(.@selected), getskillname(.@selected)));
		mes("\n");
		mes("Please choose another skill.");
		close();
	}
	// Find Corresponding Skill Lv.
	.@selected_level = 0;
	for( .@i = 0; .@i < .@count; ++.@i ) {
		if( .@skill_ids[.@i] == .@selected ) {
			.@selected_level = .@skill_lvs[.@i];
			break;
		}
	}
	// Safety check
	if( .@selected_level == 0 ) {
		mes(.npc_name$);
		mes("<b>^FF0000Error:^000000</b> Could not find skill level data.");
		close();
	}
	next();
	mes(.npc_name$);
	mes(sprintf("You selected: <b>^0000FF%s^000000</b> (^777777%s^000000) ^00AA00Lv.%d^000000", getskilldesc(.@selected), getskillname(.@selected), .@selected_level));
	mes("\n");
	mes(sprintf("Cost: ^00AA00%s Zeny^000000", callfunc("F_InsertComma", .skill_zeny)));
	mes(sprintf("Your Zeny: ^0055FF%s^000000", callfunc("F_InsertComma", Zeny)));
	mes("\n\n");
	mes("Proceed with plagiarism?");
	next();
	if( select(sprintf("- Plagiarize Skill (%s Lv.%d)", getskilldesc(.@selected), .@selected_level), "- Cancel") == 2 ) {
		mes(.npc_name$);
		mes("Please feel free to return anytime if you would like to utilize any of the skills I offer on this list.");
		close();
	}
	if( Zeny < .skill_zeny ) {
		mes(.npc_name$);
		mes("^FF0000Insufficient Zeny!^000000");
		mes(sprintf("You need at least ^00AA00%s Zeny^000000.", callfunc("F_InsertComma", .skill_zeny)));
		close();
	}
	if( getstatus(SC_PRESERVE) ) {
		sc_end(SC_PRESERVE);
	}
	if( plagiarizeskill(.@selected, .@selected_level) ) {
		Zeny -= .skill_zeny;
		specialeffect2(EF_BASH3D);
		specialeffect2(EF_STEAL);
		message(strcharinfo(PC_NAME), sprintf("Successfully Copied: %s (%s) Lv.%d", getskilldesc(.@selected), getskillname(.@selected), .@selected_level));
		mes(.npc_name$);
		mes("<b>^00AA00SUCCESS^000000</b>");
		mes(sprintf("You have plagiarized <b>^0000FF%s^000000</b> (^777777%s^000000) ^00AA00Lv.%d^000000.", getskilldesc(.@selected), getskillname(.@selected), .@selected_level));
		mes("\n");
		mes("Please use it wisely!");
	}
	else {
		mes(.npc_name$);
		mes("<b>^FF0000FAILED TO APPLY PLAGIARISM^000000</b>");
		mes("\n");
		mes(sprintf("The skill <b>^0000FF%s^000000</b> (^777777%s^000000) is not copyable.", getskilldesc(.@selected), getskillname(.@selected)));
		mes("\n");
		// Show current skill if they still have one
		.@current_id = getplagiarizedskill(1);
		if (.@current_id > 0) {
			.@current_lv = getplagiarizedskilllv(1);
			mes(sprintf("Your current skill <b>^0000FF%s^000000</b> (^777777%s^000000) ^00AA00Lv.%d^000000 remains intact.", getskilldesc(.@current_id), getskillname(.@current_id), .@current_lv));
		}
		mes("\n");
		mes("^777777Check 'skill_db.yml' for the Copyable: Plagiarism FLAG.^000000");
	}
	close();

//------------------------------------------
//-- Configuration Settings
//------------------------------------------
OnInit:
	.npc_name$ = "<b>[ ^800080Plagiarism Master^000000 ]</b>";
	.skill_zeny = 150000;
	end();
}