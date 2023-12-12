#pragma once

inline void DrawMenu()
{

	if (!GUI::open) return;

	static bool InitColors = false;
	if (!InitColors)
	{ // WeaponVisible
		ColorPicker::SkeletonsVisible = Color( 58, 214, 0, 255 );// ColorPicker::Test
		ColorPicker::SkeletonsInVisible = Color(230, 31, 0, 255 );// ColorPicker::Test

		ColorPicker::BoxVisible = Color(58, 214, 0, 255);//
		ColorPicker::BoxInVisible = Color(230, 31, 0, 255);//

		ColorPicker::TextEspVisible = Color(3, 221, 255, 255);//
		ColorPicker::TextEspInVisible = Color(255, 80, 180, 255);//

		ColorPicker::WeaponVisible = Color(3, 221, 255, 255);//
		ColorPicker::WeaponInVisible = Color(255, 80, 180, 255);//

		ColorPicker::FlagsVisible = Color(3, 221, 255, 255);//
		ColorPicker::FlagsInVisible = Color(255, 80, 180, 255);//

		ColorPicker::MovmentLine = Color(3, 221, 255, 255);//
		ColorPicker::Fov = Color(219, 65, 65, 255);//

		ColorPicker::SkyColor = Color(255, 80, 180, 255);//
		ColorPicker::AmbientColor = Color(255, 80, 180, 255);//

		ColorPicker::BulletTracer = Color(255, 255, 255, 255);//
		ColorPicker::OOFVisible = Color(58, 214, 0, 255);//

		ColorPicker::OOFInVisible = Color(230, 31, 0, 255);//
		ColorPicker::PlayerChamsVisible = Color(127, 255, 0, 255);//
		ColorPicker::PlayerChamsInVisible = Color(220, 20, 60, 255);//

		ColorPicker::HandChams2 = Color(230, 31, 0, 255);//
		ColorPicker::HandChams = Color(127, 255, 0, 255);//

		ColorPicker::RadarVisible = Color(230, 31, 0, 255);//
		ColorPicker::RadarInVisible = Color(127, 255, 0, 255);//
		InitColors = true;
	}

	const wchar_t* BoxCombo[] = { _(L"No Box Style"),_(L"Default Box"),_(L"Corner Box"), };

	const wchar_t* HealthCombo[] = { _(L"No Health Box"),_(L"Vertical Health Box"),_(L"Horizontal Health Box"), };

	const wchar_t* TargtCombo[] = { _(L"Target Head"),_(L"Target Body"), };

	const wchar_t* HitBoxOVPlayerMulti[] = { _(L"Force Override Nothing"),_(L"Force Head"),_(L"Force Body"),_(L"Force Random"),_(L"Force Random + Head") };

	main_menu_open = GUI::Window(_(L""), { 50, 50 }, { 312 , 640 }, false);
	{
		GUI::Tab(_(L"AIMBOT"), 0);
		GUI::Tab1(_(L"VISUAL"), 1);
		GUI::Tab2(_(L"GLOBAL"), 2);
		GUI::Tab3(_(L"MISC"), 3);
		//GUI::Tab(_(L"Misc"), 4);
		//GUI::Tab(_(L"Config"), 5);
		switch (Vars::ActiveTab)
		{
			///////////// COMBAT /////////////
		case 0:
			GUI::DoubleSubTab1(_(L"COMBAT"), 0);
			GUI::DoubleSubTab2(_(L"EXPLOITS"), 1);
			//GUI::subTab(_(L"FILTER"), 2);
			switch (Vars::ActuveSubTab)
			{
			case 0:
				GUI::TabChild(_(L"Combat"), { 21, 70 }, { 270, 550 });
				{
					GUI::Hotkey(&Vars::Keys::pSilent, &Vars::Keys::pSilentType, Vars::Keys::pSilentVal, &HotKey_pSilent);
					GUI::CheckBox(_(L"Silent Aim"), Vars::Aim::pSilent);
					GUI::CheckBox(_(L"Crosshair"), Vars::Aim::Cross);
					GUI::DoColorPicker(ColorPicker::Fov, ColorPicker::FovBool, true);
					GUI::CheckBox(_(L"FOV Circle"), Vars::Aim::DrawFov);
					GUI::CheckBox(_(L"Target Line"), Vars::Visuals::PlayerEsp::TargetLine);
					GUI::DoColorPicker(ColorPicker::BulletTracer, ColorPicker::BulletTracerBool, true);
					GUI::CheckBox(_(L"Bullet Tracers"), Vars::Visuals::BulletTraces); // Vars::Exploits::ShootThroughTeammates
					GUI::Combo(_(L""), &Vars::Aim::AimCombo, TargtCombo, ARRAYSIZE(TargtCombo));
					next_item_pos.y += 1.f;
					GUI::CheckBox(_(L"Ignore Visible Check"), Vars::Aim::IgnoreVisible);
					GUI::CheckBox(_(L"Ignore Helicopter"), Vars::Aim::IgnoreHeli);
					GUI::CheckBox(_(L"Ignore Turrets"), Vars::Aim::IgnoreTurrets);
					GUI::CheckBox(_(L"Ignore Wounded"), Vars::Aim::IgnoreWounded);
					GUI::CheckBox(_(L"Ignore Sleepers"), Vars::Aim::IgnoreSleepers);
					GUI::CheckBox(_(L"Ignore NPC"), Vars::Aim::IgnoreNpc);
					GUI::CheckBox(_(L"Ignore Team"), Vars::Aim::IgnoreTeam);
					GUI::CheckBox(_(L"Ignore Safe Zone"), Vars::Aim::IgnoreSafeZone);
					next_item_pos.y -= 3.f;
					GUI::IntSlider(_(L"Silent Aim Spread"), Vars::Aim::pSilentSpread, 0, 100);
					GUI::Slider(_(L"Miss Chance"), Vars::Aim::HitChance, 0, 100, _(L"%s:  %0.1f"));
					GUI::IntSlider(_(L"FOV Circle Amount"), Vars::Aim::OverrideAimFov, 0, 600);
					GUI::Slider(_(L"Recoil Amount"), Vars::Weapon::Recoil, 0, 100);
					GUI::Slider(_(L"Spread Amount"), Vars::Weapon::Spread, 0, 100);
				}
				break;
			case 1:
				GUI::TabChild(_(L"Combat Exploits"), { 21, 70 }, { 270, 550 });
				{
					GUI::CheckBox(_(L"No Sway"), Vars::Weapon::NoSway); // Vars::Weapon::NoDeployDelay
					GUI::CheckBox(_(L"No Bob"), Vars::Weapon::NoBob);
					GUI::CheckBox(_(L"No Lower"), Vars::Weapon::NoLower);
					GUI::CheckBox(_(L"Jump Shoot"), Vars::Misc::JumpShoot);
					GUI::CheckBox(_(L"Shoot Mounted"), Vars::Misc::ShootMounted);
					GUI::CheckBox(_(L"Instant Eoka"), Vars::Weapon::InstaEoka);
					GUI::CheckBox(_(L"Full Auto"), Vars::Weapon::FullAuto);
					GUI::CheckBox(_(L"Shoot Through Teammates"), Vars::Exploits::ShootThroughTeammates);
					GUI::CheckBox(_(L"Heli Override"), Vars::Exploits::HeliOverride);
					GUI::CheckBox(_(L"Magic Helicopter"), Vars::Exploits::HeliMagic);
					GUI::CheckBox(_(L"Big Bullet"), Vars::Weapon::FatBullet);
					next_item_pos.y -= 1.f;
					if (Vars::Weapon::FatBullet) // LongMelee
						GUI::Slider(_(L"Thickness"), Vars::Weapon::FatBulletValue, 0, 0.65);
					next_item_pos.y += 4.f;
					GUI::Combo(_(L"Hitbox Override"), &Vars::Exploits::PlayerOverride, HitBoxOVPlayerMulti, ARRAYSIZE(HitBoxOVPlayerMulti));
					//GUI::CheckBox(_(L"No Animation"), Vars::Weapon::NoAnimation);
				}
				break;
			//case 2:
			//	GUI::TabChild(_(L""), { 21, 70 }, { 270, 550 });
			//	{
			//		//GUI::CheckBox(_(L"Target InVisible"), Vars::Aim::IgnoreVisible);
			//		//GUI::CheckBox(_(L"Ignore Heli"), Vars::Aim::IgnoreHeli);
			//		//GUI::CheckBox(_(L"Ignore Turrets"), Vars::Aim::IgnoreTurrets);
			//		//GUI::CheckBox(_(L"Ignore Wounded"), Vars::Aim::IgnoreWounded);
			//		//GUI::CheckBox(_(L"Ignore Sleepers"), Vars::Aim::IgnoreSleepers);
			//		//GUI::CheckBox(_(L"Ignore Npc"), Vars::Aim::IgnoreNpc);
			//		//GUI::CheckBox(_(L"Ignore Team"), Vars::Aim::IgnoreTeam);
			//		//GUI::CheckBox(_(L"Ignore SafeZone"), Vars::Aim::IgnoreSafeZone);
			//		//GUI::CheckBox(_(L"Crosshair"), Vars::Aim::Cross);
			//	}
			//	break;
			}

			break;
			///////////// PLAYER ESP /////////////
		case 1:
			GUI::DoubleSubTab3(_(L"PLAYER"), 0);
			GUI::DoubleSubTab4(_(L"OTHER"), 1);
			switch (Vars::ActuveSubTab)
			{
			case 0:
				GUI::TabChild(_(L"Player Visuals"), { 21, 70 }, { 270, 550 });
				{
					GUI::DoColorPicker(ColorPicker::TextEspVisible, ColorPicker::TextEspVisBool, false);
					GUI::DoColorPicker(ColorPicker::TextEspInVisible, ColorPicker::TextEspInVisBool, true);
					//GUI::ColorPicker({ next_item_pos.x + 230, next_item_pos.y }, ColorPicker::TextEspInVisBool, ColorPicker::TextEspInVisible, ColorPicker::TextRGBBool);
					GUI::CheckBox(_(L"Name"), Vars::Visuals::PlayerEsp::NameEsp);
					GUI::DoColorPicker(ColorPicker::WeaponVisible, ColorPicker::WeaponVisBool, false);
					GUI::DoColorPicker(ColorPicker::WeaponInVisible, ColorPicker::WeaponInVisBool, true);

					GUI::CheckBox(_(L"Weapon"), Vars::Visuals::PlayerEsp::WeaponEsp);
					GUI::CheckBox(_(L"Distance"), Vars::Visuals::PlayerEsp::DistanceEsp);
					GUI::CheckBox(_(L"Look Direction"), Vars::Visuals::PlayerEsp::LookDirection);

					GUI::DoColorPicker(ColorPicker::FlagsVisible, ColorPicker::FlagsVisBool, false);
					GUI::DoColorPicker(ColorPicker::FlagsInVisible, ColorPicker::FlagsInVisBool, true);

					GUI::CheckBox(_(L"Flags"), Vars::Visuals::PlayerEsp::ShowPlayerFlags);

					GUI::DoColorPicker(ColorPicker::SkeletonsVisible, ColorPicker::SkeletonsVisBool, false);
					GUI::DoColorPicker(ColorPicker::SkeletonsInVisible, ColorPicker::SkeletonsInVisBool, true);

					GUI::CheckBox(_(L"Skeleton"), Vars::Visuals::PlayerEsp::Skeleton);

					GUI::DoColorPicker(ColorPicker::BoxVisible, ColorPicker::BoxVisBool, false);
					GUI::DoColorPicker(ColorPicker::BoxInVisible, ColorPicker::BoxInVisBool, true);

					GUI::Combo(_(L"Health ESP"), &Vars::Visuals::PlayerEsp::HealthEsp, HealthCombo, ARRAYSIZE(HealthCombo));
					next_item_pos.y += 1.f;
					GUI::Combo(_(L"Box ESP"), &Vars::Visuals::PlayerEsp::BoxEsp, BoxCombo, ARRAYSIZE(BoxCombo));
				}
				break;
			case 1:
				GUI::TabChild(_(L"Indicators"), { 21, 70 }, { 270, 275 });
				{
					GUI::DoColorPicker(ColorPicker::OOFVisible, ColorPicker::OOFVisBool, false);
					GUI::DoColorPicker(ColorPicker::OOFInVisible, ColorPicker::OOFInVisBool, true);
					GUI::CheckBox(_(L"Enemy Indicator"), Vars::Visuals::PlayerEsp::OOFindicators); // Radar
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Range"), Vars::Visuals::PlayerEsp::OOFDist, 0, 600);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Radar"), Vars::Visuals::PlayerEsp::Radar); // 
					GUI::CheckBox(_(L"Look Direction"), Vars::Visuals::PlayerEsp::Radar_ld); // 
					GUI::CheckBox(_(L"Target Hotbar"), Vars::Visuals::PlayerEsp::TargetHotBar);
					GUI::CheckBox(_(L"Show Teammates"), Vars::Visuals::PlayerEsp::TeamEsp);
					GUI::CheckBox(_(L"Show NPC"), Vars::Visuals::PlayerEsp::NpcEsp);
					GUI::CheckBox(_(L"Show Sleeper"), Vars::Visuals::PlayerEsp::SleeperEsp);
				}
				GUI::TabChild(_(L"Game"), { 21, 365 }, { 270, 255 });
				{
					GUI::CheckBox(_(L"Bright Night"), Vars::Misc::BrightNight);
					GUI::CheckBox(_(L"Time Changer"), Vars::Misc::TimeChanger);
					next_item_pos.y -= 1.f;
					//if (Vars::Misc::TimeChanger)
					GUI::Slider(_(L"Time"), Vars::Misc::GameTime, 0, 24);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Player FOV"), Vars::Misc::PlayerFovBool);
					next_item_pos.y -= 1.f;
					//if (Vars::Misc::PlayerFovBool)
					GUI::IntSlider(_(L"FOV"), Vars::Misc::PlayerFov, 0, 140);
					next_item_pos.y += 4.f;

					GUI::Hotkey(&Vars::Keys::Zoom, &Vars::Keys::ZoomType, Vars::Keys::ZoomVal, &HotKey_Zoom);
					GUI::CheckBox(_(L"Zoom"), Vars::Misc::PlayerZoomBool);
					next_item_pos.y -= 1.f;
					//if (Vars::Misc::PlayerZoomBool)
					GUI::IntSlider(_(L"Zoom"), Vars::Misc::Zoom, 0, 140);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Aspect Ratio"), Vars::Misc::AspectRatio);
					next_item_pos.y -= 1.f;
					//if (Vars::Misc::AspectRatio)
					GUI::Slider(_(L"Aspect Ratio"), Vars::Misc::Aspect, 0, 3); // Vars::Misc::SkyColor
					next_item_pos.y += 4.f;
				}
				break;
			}


			break;

		case 2:

			GUI::subTab(_(L"TAB 1"), 0);
			GUI::subTab(_(L"TAB 2"), 1);
			GUI::subTab(_(L"TAB 3"), 2);
			GUI::subTab(_(L"TAB 4"), 3);
			switch (Vars::ActuveSubTab)
			{
			case 0:
				GUI::TabChild(_(L"Ores"), { 21, 70 }, { 270, 275 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::DrawdDstance, 0, 300);
					next_item_pos.y += 4.f;
					next_item_pos.x += 160.f;
					//next_item_pos.y -= 20;
					// GUI::CheckBox(_(L"Draw Hp"), Vars::Visuals::OreHealth, 160, 3);
					next_item_pos.x -= 160.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::DrawdDstanceBool);
					//GUI::CheckBox(_(L"Ore Health"), Vars::Visuals::OreHealth);
					GUI::CheckBox(_(L"Stone Ore"), Vars::Visuals::StoneOre);
					GUI::CheckBox(_(L"Metal Ore"), Vars::Visuals::MetalOre);
					GUI::CheckBox(_(L"Sulfur Ore"), Vars::Visuals::SulfurOre);
				}
				GUI::TabChild(_(L"Crates"), { 21, 365 }, { 270, 255 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::CrateDstance, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::CrateDstanceBool);
					GUI::CheckBox(_(L"Elite Crate"), Vars::Visuals::EliteCrate);
					GUI::CheckBox(_(L"Basic Crate"), Vars::Visuals::BasicCrate);
					GUI::CheckBox(_(L"Military Crate"), Vars::Visuals::NormalCrate);
					GUI::CheckBox(_(L"Normal Crate"), Vars::Visuals::NormalCrate2);
					GUI::CheckBox(_(L"Tool Crate"), Vars::Visuals::ToolCrate);
				}
				break;
			case 1:
				GUI::TabChild(_(L"Traps"), { 21, 70 }, { 270, 275 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::TrapDstance, 0, 300);
					next_item_pos.y += 4.f;
					//next_item_pos.x += 160.f;
					//next_item_pos.y -= 20;
					GUI::CheckBox(_(L"Draw HP"), Vars::Visuals::TrapHealth, 160, 3);
					//next_item_pos.x -= 160.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::TrapDstanceBool);
					GUI::CheckBox(_(L"Flame Turret"), Vars::Visuals::FlameTurret);
					GUI::CheckBox(_(L"Bear Trap"), Vars::Visuals::BearTrap);
					GUI::CheckBox(_(L"Turrets"), Vars::Visuals::Turrents);
					GUI::CheckBox(_(L"SAM Site"), Vars::Visuals::SamSite);
					GUI::CheckBox(_(L"Gun Trap"), Vars::Visuals::Guntrap);
					GUI::CheckBox(_(L"Land Mine"), Vars::Visuals::LandMine);
				}
				GUI::TabChild(_(L"Animals"), { 21, 365 }, { 270, 255 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::DistanceAnimal, 0, 300);
					next_item_pos.y += 4.f;
					//next_item_pos.x += 160.f;
					//next_item_pos.y -= 20;
					GUI::CheckBox(_(L"Draw HP"), Vars::Visuals::AnimalHealth, 160, 3);
					//next_item_pos.x -= 160.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::DistanceAnimalBool);
					GUI::CheckBox(_(L"Boar"), Vars::Visuals::Boar);
					GUI::CheckBox(_(L"Bear"), Vars::Visuals::Bear);
					GUI::CheckBox(_(L"Horse"), Vars::Visuals::Horse);
					GUI::CheckBox(_(L"Wolf"), Vars::Visuals::Wolf);
				}
				break;
			case 2:
				GUI::TabChild(_(L"Vehicles"), { 21, 70 }, { 270, 275 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::VehicleDstance, 0, 300);
					next_item_pos.y += 4.f;
					//next_item_pos.x += 160.f;
					//next_item_pos.y -= 20;
					GUI::CheckBox(_(L"Draw HP"), Vars::Visuals::VehicleHealth, 160, 3);
					//next_item_pos.x -= 160.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::VehicleDistanceBool);
					GUI::CheckBox(_(L"Minicopter"), Vars::Visuals::Minicopter);
					GUI::CheckBox(_(L"Bradley"), Vars::Visuals::Bradley);
					GUI::CheckBox(_(L"Rowboat"), Vars::Visuals::Rowboat);
					GUI::CheckBox(_(L"RHIB"), Vars::Visuals::Rhib);
					GUI::CheckBox(_(L"Scrap Transport Heli"), Vars::Visuals::ScrapTransportHeli);
					GUI::CheckBox(_(L"Patrol Helicopter"), Vars::Visuals::PatrolHelicopter);
				}
				GUI::TabChild(_(L"Plants"), { 21, 365 }, { 270, 255 });
				{
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::BerryDstance, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::BerryDistanceBool);
					GUI::CheckBox(_(L"Blue Berry"), Vars::Visuals::BlueBerry);
					GUI::CheckBox(_(L"Yellow Berry"), Vars::Visuals::YellowBerry);
					GUI::CheckBox(_(L"Red Berry"), Vars::Visuals::RedBerry);
					GUI::CheckBox(_(L"Green Berry"), Vars::Visuals::GreenBerry);

					//next_item_pos.y += 4.f;

					GUI::CheckBox(_(L"Hemp"), Vars::Visuals::Hemp);
					if (Vars::Visuals::Hemp)
					{
						GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::HempDistanceBool);
						next_item_pos.y -= 1.f;
						GUI::Slider(_(L"Distance"), Vars::Visuals::HempDistance, 0, 300);
					}
				}
				break;
			case 3:
				GUI::TabChild(_(L"Other"), { 21, 70 }, { 270, 550 });
				{
					//next_item_pos.y -= 20.f;
					GUI::CheckBox(_(L"Dropped Items"), Vars::Visuals::DroppedItems);
					//next_item_pos.y -= 1.f;
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::DroppedItemsDistBool);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::DroppedItemsDist, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Corpse"), Vars::Visuals::Corpse);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::CorpseDrawDist);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::CorpseDist, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Backpack"), Vars::Visuals::BackPack);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::BackPackDrawDist);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::BackPackDist, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Hackable Crate"), Vars::Visuals::HackableCrate);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::HackableCrateDrawDist);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::HackableCrateDist, 0, 10000);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Tool Cupboard"), Vars::Visuals::ToolCupboard);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::ToolCupboardDrawDist);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::ToolCupboardDist, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Stash"), Vars::Visuals::Stash);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::StashDrawDist);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::StashDist, 0, 300);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Diesel Barrel"), Vars::Visuals::Diesel);
					GUI::CheckBox(_(L"Draw Distance"), Vars::Visuals::DieselDistBool);
					next_item_pos.y -= 1.f;
					GUI::Slider(_(L"Distance"), Vars::Visuals::DieselDist, 0, 300);
					next_item_pos.y += 4.f;
				}
				break;
			}

			break;

			///////////// OBJECT ESP /////////////

		case 3:
			GUI::DoubleSubTab5(_(L"CONFIG"), 0);
			GUI::DoubleSubTab6(_(L"EXPLOITS"), 1);
			switch (Vars::ActuveSubTab)
			{
			case 0:
				GUI::TabChild(_(L""), { 21, 70 }, { 270, 550 });
				{

				}
				break;
			case 1:
				GUI::TabChild(_(L"Movement"), { 21, 70 }, { 270, 275 });
				{
					GUI::CheckBox(_(L"No Fall Damage"), Vars::Misc::NoFallDamage);
					GUI::CheckBox(_(L"Spider"), Vars::Misc::SpiderMan);
					GUI::CheckBox(_(L"Small Capsule"), Vars::Misc::SpiderManBypass);
					GUI::CheckBox(_(L"Infinite Jump"), Vars::Misc::InfinityJump);
					GUI::Hotkey(&Vars::Keys::FlyKey, &Vars::Keys::FlyKeyType, Vars::Keys::FlyVal, &HotKey_FlyKey);
					GUI::CheckBox(_(L"Fly Hack"), Vars::Misc::InteractiveFly); // Vars::Misc::FlySpeed
					next_item_pos.y -= 1.f;
					GUI::IntSlider(_(L"Speed Amount"), Vars::Misc::FlySpeed, 0, 10);
					next_item_pos.y += 4.f;
					GUI::CheckBox(_(L"Fly Hack Bar"), Vars::Misc::FlyHackBar);
					GUI::CheckBox(_(L"Anti Fly Kick"), Vars::Misc::AntiFlyKick);
					GUI::CheckBox(_(L"Anti InsideTerrain Kick"), Vars::Misc::AntiInsideTerrain);
				}
				GUI::TabChild(_(L"Misc"), { 21, 365 }, { 270, 255 });
				{
					GUI::CheckBox(_(L"Mass Suicide"), Vars::Misc::MassSuicide);
					GUI::Hotkey(&Vars::Keys::SilentStash, &Vars::Keys::SilentStashType, Vars::Keys::SilentStashVal, &HotKey_SilentStash); // Vars::Misc::ShootMounted
					GUI::CheckBox(_(L"Silent Stash"), Vars::Misc::SilentStash);
					GUI::CheckBox(_(L"Admin Flag"), Vars::Misc::AdminFlag);
					GUI::CheckBox(_(L"Block Server Commands"), Vars::Misc::BlockCommands);
					GUI::CheckBox(_(L"Instant Loot"), Vars::Misc::FastLoot);
					GUI::CheckBox(_(L"Resource Hotspot"), Vars::Misc::AlwaysHotSpot);
					GUI::CheckBox(_(L"Auto Pickup Loot"), Vars::Misc::AutoPickupLoot);
					GUI::CheckBox(_(L"Auto Heal"), Vars::Misc::autoHeal);

				}
				break;
			}			break;
			///////////// MISC /////////////

		}
	}
	GUI::end_window();
	return;
}
Vector3 TargetOrePos = Vector3::Zero();
bool Pressed111 = false;
bool Open111 = false;
bool initongui = false;

float MovePosMenu = 0;
float rainbow = 0.00;
float rotationdegree = 0.000;

//void SwastikaCrosshair()
//{
//	Vector2 Screen = Vector2(Vars::ScreenWidth, Vars::ScreenHeight);
//	Vector2 Middle; Middle.x = (int)(Screen.x / 2); Middle.y = (int)(Screen.y / 2);
//	int a = (int)(Screen.y / 2 / 120);
//	float gamma = Maths::m_Atan(a / a);
//
//	if ((int)rotationdegree > 89) { rotationdegree = (float)0; }
//
//	int i = 0;
//	while (i < 4)
//	{
//		float p_0 = (a * Maths::m_Sin(DEG2RAD(rotationdegree + (i * 90))));
//		float p_1 = (a * Maths::m_Cos(DEG2RAD(rotationdegree + (i * 90))));
//		float p_2 = ((a / Maths::m_Cos(gamma)) * Maths::m_Sin(DEG2RAD(rotationdegree + (i * 90) + RAD2DEG(gamma))));
//		float p_3 = ((a / Maths::m_Cos(gamma)) * Maths::m_Cos(DEG2RAD(rotationdegree + (i * 90) + RAD2DEG(gamma))));
//
//		GUI::DrawLine({ Middle.x, Middle.y }, { Middle.x + p_0, Middle.y - p_1 }, { 255,255,255,255 }, 1.2, true);
//		GUI::DrawLine({ Middle.x + p_0, Middle.y - p_1 }, { Middle.x + p_2, Middle.y - p_3 }, { 255,255,255,255 }, 1.2, true);
//
//		i++;
//	}
//
//	rotationdegree++;
//}


DWORD64 FakeCursor = 0;
void OnGUI(DWORD64 rcx) {



	/*auto klazz = Il2cpp::InitClass(_("MainMenuSystem"), _(""));
	UINT64 st = safe_read(klazz + 0xB8, UINT64);
	bool isMainMenuOpen = Read<bool>(st + 0x0);
	MainMenuOpen = isMainMenuOpen;*/

	GUI::InitializeAADrawing();
	if (GUI::LineTexture)
		g_WhiteTexture = GUI::LineTexture/*get_whiteTexture()*/;
	GUI::InitGL();
	GUI::Init();
	//static bool inited_assets = false;
	//if (!inited_assets) {
	//	GUI::InitAssets(); inited_assets = true;
	//}
		

	DWORD64 Event = GUI::get_current();
	EventType type = GUI::get_type(Event);

	

	if (gl_material && inited)
	{
		/*********** KEYBINDS ***********/
		if (type == EventType::KeyDown || type == EventType::KeyUp) {
			KeyCode cur = Unity::get_keyCode(Event);
			if (type == EventType::KeyDown)
				GUI::OnKeyDown(cur);
			else
				GUI::OnKeyUp(cur);
		}

		static bool isManipulating = false;
		isManipulating = GUI::KeyBind(Vars::Keys::ManipulationKey, Vars::Keys::Manip, Vars::Keys::isManip, Vars::Keys::ManipulationKeyType) || Vars::Keys::ManipulationKey == 0 || Vars::Keys::ManipulationKey == 27;
		Manipulating = isManipulating;

		static bool isDebugging = false;
		isDebugging = GUI::KeyBind(Vars::Keys::InteractiveDebugKey, Vars::Keys::InteractiveDebug, Vars::Keys::isInteractiveDebug, Vars::Keys::InteractiveDebugType) || Vars::Keys::InteractiveDebugKey == 0 || Vars::Keys::InteractiveDebugKey == 27;
		Debugging = isDebugging;

		static bool ispSilenting = false;
		ispSilenting = GUI::KeyBind(Vars::Keys::pSilent, Vars::Keys::pSilenting, Vars::Keys::ispSilent, Vars::Keys::pSilentType) || Vars::Keys::pSilent == 0 || Vars::Keys::pSilent == 27;
		PSilenting = ispSilenting;

		static bool isTeleportingToPlayersHead = false;
		isTeleportingToPlayersHead = GUI::KeyBind(Vars::Keys::TptoHead, Vars::Keys::TptoHeading, Vars::Keys::isTptoHead, Vars::Keys::TptoHeadType) || Vars::Keys::TptoHead == 0 || Vars::Keys::TptoHead == 27;
		TeleportingToPlayersHead = isTeleportingToPlayersHead;

		static bool isFlying = false;
		isFlying = GUI::KeyBind(Vars::Keys::FlyKey, Vars::Keys::Fly, Vars::Keys::isFly, Vars::Keys::FlyKeyType) || Vars::Keys::FlyKey == 0 || Vars::Keys::FlyKey == 27;
		Flying = isFlying;

		static bool isAutoShooting = false;
		isAutoShooting = GUI::KeyBind(Vars::Keys::AutoShoot, Vars::Keys::AutoShooting, Vars::Keys::isAutoShooting, Vars::Keys::AutoShootType) || Vars::Keys::AutoShoot == 0 || Vars::Keys::AutoShoot == 27;
		AutoShooting = isAutoShooting;

		static bool isFakeShooting = false;
		isFakeShooting = GUI::KeyBind(Vars::Keys::FakeShootKey, Vars::Keys::FakeShoot, Vars::Keys::isFakeShoot, Vars::Keys::FakeShootType) || Vars::Keys::FakeShootKey == 0 || Vars::Keys::FakeShootKey == 27;
		FakeShooting = isFakeShooting;

		static bool isZoominging = false;
		isZoominging = GUI::KeyBind(Vars::Keys::Zoom, Vars::Keys::Zooming, Vars::Keys::isZoom, Vars::Keys::ZoomType) || Vars::Keys::Zoom == 0 || Vars::Keys::Zoom == 27;
		Zooming = isZoominging;

		static bool isOnLaddering = false;
		isOnLaddering = GUI::KeyBind(Vars::Keys::OnLadder, Vars::Keys::OnLaddering, Vars::Keys::isOnLadder, Vars::Keys::OnLadderType) || Vars::Keys::OnLadder == 0 || Vars::Keys::OnLadder == 27;
		OnLaddering = isOnLaddering;

		static bool isTrashEsp = false;
		isTrashEsp = GUI::KeyBind(Vars::Keys::TrashEsp, Vars::Keys::TrashEsping, Vars::Keys::isOnLadder, Vars::Keys::TrashEspType) || Vars::Keys::TrashEsp == 0 || Vars::Keys::TrashEsp == 27;
		TrashEsp = isTrashEsp;

		static bool isSilentStashing = false;
		isSilentStashing = GUI::KeyBind(Vars::Keys::SilentStash, Vars::Keys::SilentStashing, Vars::Keys::isSilentStash, Vars::Keys::SilentStashType) || Vars::Keys::SilentStash == 0 || Vars::Keys::SilentStash == 27;
		SilentStashing = isSilentStashing;

		static bool isKeepTargeting = false;
		isKeepTargeting = GUI::KeyBind(Vars::Keys::KeepTarget, Vars::Keys::KeepTargeting, Vars::Keys::isKeepTarget, Vars::Keys::KeepTargetType) || Vars::Keys::KeepTarget == 0 || Vars::Keys::KeepTarget == 27;
		KeepTargeting = isKeepTargeting;

		static bool isOverridingSpeed = false;
		isOverridingSpeed = GUI::KeyBind(Vars::Keys::OVBulletSpeed, Vars::Keys::OVBulletSpeeding, Vars::Keys::isOVBulletSpeed, Vars::Keys::OVBulletSpeedType) || Vars::Keys::OVBulletSpeed == 0 || Vars::Keys::OVBulletSpeed == 27;
		OverridingSpeed = isOverridingSpeed;

		static bool isToggleFriend = false;
		isToggleFriend = GUI::KeyBind(Vars::Keys::ToggleFriend, Vars::Keys::ToggleFriend_, Vars::Keys::isToggleFriend, Vars::Keys::ToggleFriendType) || Vars::Keys::ToggleFriend == 0 || Vars::Keys::ToggleFriend == 27;
		ToggleFriend = isToggleFriend;

		static bool isToggleEnemy = false;
		isToggleEnemy = GUI::KeyBind(Vars::Keys::ToggleEnemy, Vars::Keys::ToggleEnemy_, Vars::Keys::isToggleEnemy, Vars::Keys::ToggleEnemyType) || Vars::Keys::ToggleEnemy == 0 || Vars::Keys::ToggleEnemy == 27;
		ToggleEnemy = isToggleEnemy;

		if (type == EventType::Repaint) {

			/*	if (!FakeCursor) FakeCursor = Il2cpp::object_new(Il2cpp::InitClass(_("Cursor"), _("UnityEngine")));
				reinterpret_cast<void (*)(DWORD64,bool)>((DWORD64)(g_Base + 0x2541610))(FakeCursor, false);*/
				//set_visCursor(true);

				// GUI::DrawFadeRect(20, 20, 50, 50, { 255,0,0,255 }, { 255,0,0,0 }, true);

			float CurPos = 0;
			/*********** KEYBINDS ***********/
			

			float ScreenWidth = Vars::ScreenWidth = Unity::get_width();
			float ScreenHeight = Vars::ScreenHeight = Unity::get_height();

			float x = Vars::ScreenWidth / 2, y = Vars::ScreenHeight / 2;

			/*wchar_t Dist[512];
			Str string = Unity::Format(_(L"%s"), _(L"GAYSEXWITHGAYS"), _(L"1"), _(L"1"));
			GUI::String({ 20,40, 200, 20 }, string, { 255,255,255,255 });*/

			// wformat
			// GUI::String({ 20,40, 200, 20 }, wformat(_(L"%s"), _(L"Anus")), {255,255,255,255});
			if (Vars::Misc::WaterMark)
				GUI::DrawPng({ 15, 15, 300, 150 });

			if (Vars::Visuals::PlayerEsp::Radar)
				DrawRadar();

			// GUI::DrawLine({ 10,10 }, { 30,30 }, { 255,255,255,255 }, 3, true);
			// Format
			/*DWORD64 textObj[1] = { c, };
			wchar_t Dist[512];*/


			Esp::PlayerLoop();
			Esp::ESPLoop();

			if (Vars::Aim::DrawFov) GUI::drawFov();

			if (Vars::Aim::Cross)
			{

				//GUI::String({ 0, 0, ScreenWidth, ScreenHeight + 2 }, _(L"✜"), { 255,255,255,255 }, true, 12);
				GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), { 219, 65, 65,255 }, Vector2::Zero2(), 0, Vector2(ScreenWidth / 2, ScreenHeight / 2 - 4), Vector2(ScreenWidth / 2, ScreenHeight / 2 + 4));
				GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), { 219, 65, 65,255 }, Vector2::Zero2(), 0, Vector2(ScreenWidth / 2 - 4, ScreenHeight / 2), Vector2(ScreenWidth / 2 + 4, ScreenHeight / 2));
			}
			//if (Vars::Aim::Cross == 2)
			//{
			//	//GUI::String({ 0, 0, ScreenWidth, ScreenHeight  }, _(L"."), { 255,255,255,255 }, true, 16);
			//	GUI::FillBoxRounded(Rect(ScreenWidth / 2 - 2, ScreenHeight / 2 - 2, 5, 5), { 0, 0, 0, 170 }, ScaleMode::ScaleToFit, 360);
			//	GUI::FillBoxRounded(Rect(ScreenWidth / 2 - 1, ScreenHeight / 2 - 1, 3, 3), { 255,255,255,255 }, ScaleMode::ScaleToFit, 360);
			//} // 
			//if (Vars::Aim::Cross == 3)
			//{
			//	SwastikaCrosshair();
			//}

			if (LocalPlayer)
			{
				float IndicatorPos = 0;

				//if (Vars::Visuals::DesyncBar)// && (Vars::Exploits::Manipulation && Unity::GetKeyInt(Vars::Keys::ManipulationKey) || Vars::Exploits::InstaKill && Unity::GetKeyInt(Vars::Keys::InstaKillKey)))
				//{
				//	if (Vars::Misc::Indicator == 0) {
				//		float x = Vars::ScreenWidth / 2, y = Vars::ScreenHeight / 2;
				//		x -= 50;

				//		float EntDesync = 0.0;
				//		if (Manipulating && Vars::Exploits::Manipulation)
				//		{
				//			EntDesync = Vars::Exploits::DesyncTime;

				//			GUI::DrawBar({ x , y + 35 }, { 100, 4.3 }, EntDesync, 1.0f);
				//			IndicatorPos += 7;
				//		}
				//		else EntDesync = 0.0;
				//	}
					//else if (Vars::Misc::Indicator == 1) {
					//	float x = Vars::ScreenWidth / 2, y = Vars::ScreenHeight / 2;
					//	x -= 70;

					//	float EntDesync = 0.0;
					//	if (Manipulating)
					//	{
					//		EntDesync = Vars::Exploits::DesyncTime;

					//		GUI::DrawBar2({ x , y + 15 }, { 140, 4.3 }, EntDesync, 1.0f);
					//		IndicatorPos += 7;
					//	}
					//}
				//}
				if (Vars::Misc::FlyHackBar)
				{
					GUI::DrawBar({ x - 150 , 40 }, { 300, 10 }, flyhackDistanceVertical, Vars::Misc::MaxVerticalFly);
					GUI::DrawBar({ x - 150, 52 }, { 300, 10 }, flyhackDistanceHorizontal, Vars::Misc::MaxHorizontalFly);
				}

				float IndPos2 = 0;
				if (Vars::Misc::InteractiveDebug && Debugging)
				{
					GUI::String({ x - 75, 90,150, 40 }, _(L"Debug Camera"), { 255,0,0,255 }, true, 9);
					IndPos2 += 15;
				}

				if (Vars::Misc::InteractiveFly && Flying)
				{
					GUI::String({ x - 75, 90 + IndPos2,150, 40 }, _(L"Fly Hack"), { 255,0,0,255 }, true, 9);
					IndPos2 += 15;
				}
			}

			// UnityConfig::Save();

			

			/*if (save)*/
			/*if (load) cfg->Config(configType::Load, global::menu::activeConfig);
			if (_delete) cfg->Config(configType::Delete, global::menu::activeConfig);*/
			// DrawMenu();
			// myConfigs::Config(configType::Save ,1 );
			//config::Config();
			
			// DrawNewMenu();


			// LastDesyncDist = max(LastDesyncDist, num7);

			/*wchar_t outputText[512];
			f_swprint(outputText, _(L"%0.3f"), LastDesyncDist);
			GUI::String({ 20, 20, 400, 20 }, outputText, Color(255,255,255,255), false, 10);*/

			DrawMenu();
		}
	}

}
float lastupdatetime = 0.0;


//void Esp::Chams(BasePlayer* Player)
//{
//	if (Vars::Visuals::PlayerEsp::PlayerChams)
//	{
//		auto _multiMesh = Read<DWORD64>((DWORD64)Player->GetPlayerModel() + 0x270); //SkinnedMultiMesh _multiMesh;
//		if (_multiMesh) {
//			auto render = Classes::get_Renderers(_multiMesh);
//			for (int i = 0; i < render->GetSize(); i++) {
//				auto renderer = render->GetValue(i);
//				if (renderer) {
//					DWORD64 material = Classes::get_material(renderer);
//					if (material) {
//
//						//if (ForceField_shader == 0 || chams_shader == 0 || xray_shader == 0 || hologram_shader == 0) return;
//						// if (!Unity::CanOverWriteAssets && (Vars::Visuals::PlayerEsp::PlayerChamsType == 1 && ForceField_shader != Classes::get_shader(material)) || (Vars::Visuals::PlayerEsp::PlayerChamsType == 2 && chams_shader != Classes::get_shader(material)) || (Vars::Visuals::PlayerEsp::PlayerChamsType == 3 && xray_shader != Classes::get_shader(material)) || (Vars::Visuals::PlayerEsp::PlayerChamsType == 4 && hologram_shader != Classes::get_shader(material)))
//						if (!Unity::CanOverWriteAssets)
//						{
//							static DWORD64 chamsMat1 = 0;
//							static DWORD64 chamsMat2 = 0;
//							switch (Vars::Visuals::PlayerEsp::PlayerChamsType)
//							{
//							case 0:
//								if (StormShader != Classes::get_material((DWORD64)renderer)) {
//									Unity::set_material(renderer, StormShader);
//									chamsMat2 = Classes::get_material((DWORD64)renderer);
//									// GUI::SetInt((DWORD64)chamsMat2, _(L"rainbow_go"), 0);
//								}
//								break;
//							case 1: // GalaxyPink
//								if (GalaxyPink != Classes::get_material((DWORD64)renderer)) {
//									Unity::set_material(renderer, GalaxyPink);
//								}
//								break;
//							case 2:
//								if (GalaxyGreen != Classes::get_material((DWORD64)renderer)) {
//									Unity::set_material(renderer, GalaxyGreen);
//								}
//								break;
//							case 3:
//								if (GalaxyRed != Classes::get_material((DWORD64)renderer)) {
//									Unity::set_material(renderer, GalaxyRed);
//								}
//								break;
//							case 4:
//								if (GalaxyBlue != Classes::get_material((DWORD64)renderer)) {
//									Unity::set_material(renderer, GalaxyBlue);
//								}
//								break;
//							}
//
//						}
//					}
//				}
//			}
//		}
//	}
//
//}


inline void DrawSkeleton(BasePlayer* Player, Color clr, float Wight)
{
	if (Vars::Visuals::PlayerEsp::Skeleton) {

		auto head_b = Player->GetTransform(head)->Position();
		auto spine4_b = Player->GetTransform(spine4)->Position();
		auto l_upperarm_b = Player->GetTransform(l_upperarm)->Position();
		auto l_forearm_b = Player->GetTransform(l_forearm)->Position();
		auto l_hand_b = Player->GetTransform(l_hand)->Position();
		auto r_upperarm_b = Player->GetTransform(r_upperarm)->Position();
		auto r_forearm_b = Player->GetTransform(r_forearm)->Position();
		auto r_hand_b = Player->GetTransform(r_hand)->Position();
		auto pelvis_b = Player->GetTransform(pelvis)->Position();
		auto l_hip_b = Player->GetTransform(l_hip)->Position();
		auto l_knee_b = Player->GetTransform(l_knee)->Position();
		auto l_foot_b = Player->GetTransform(l_foot)->Position();
		auto r_hip_b = Player->GetTransform(r_hip)->Position();
		auto r_knee_b = Player->GetTransform(r_knee)->Position();
		auto r_foot_b = Player->GetTransform(r_foot)->Position();
		auto r_toe_b = Player->GetTransform(r_toe)->Position();
		auto l_toe_b = Player->GetTransform(l_toe)->Position();

		Vector2 head, spine, l_upperarm, l_forearm, l_hand, r_upperarm, r_forearm, r_hand, pelvis, l_hip, l_knee, l_foot, r_hip, r_knee, r_foot, l_toe, r_toe;
		if (WorldToScreen(head_b, head) &&
			WorldToScreen(spine4_b, spine) &&
			WorldToScreen(l_upperarm_b, l_upperarm) &&
			WorldToScreen(l_forearm_b, l_forearm) &&
			WorldToScreen(l_hand_b, l_hand) &&
			WorldToScreen(r_upperarm_b, r_upperarm) &&
			WorldToScreen(r_forearm_b, r_forearm) &&
			WorldToScreen(r_hand_b, r_hand) &&
			WorldToScreen(pelvis_b, pelvis) &&
			WorldToScreen(l_hip_b, l_hip) &&
			WorldToScreen(l_knee_b, l_knee) &&
			WorldToScreen(l_foot_b, l_foot) &&
			WorldToScreen(r_hip_b, r_hip) &&
			WorldToScreen(r_knee_b, r_knee) &&
			WorldToScreen(r_toe_b, r_toe) &&
			WorldToScreen(l_toe_b, l_toe) &&
			WorldToScreen(r_foot_b, r_foot)) {

			/*GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, head, spine);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, spine, l_upperarm);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, l_upperarm, l_forearm);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, l_forearm, l_hand);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, spine, r_upperarm);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, r_upperarm, r_forearm);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, r_forearm, r_hand);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, spine, pelvis);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, pelvis, l_hip);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, l_hip, l_knee);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, l_knee, l_foot);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, pelvis, r_hip);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, r_hip, r_knee);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, r_knee, r_foot);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, r_foot, r_toe);
			GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), clr, Vector2::Zero2(), 0.f, l_foot, l_toe);*/

			GUI::DrawLine(head, spine, clr, Wight, true);
			GUI::DrawLine(spine, l_upperarm, clr, Wight, true);
			GUI::DrawLine(l_upperarm, l_forearm, clr, Wight, true);
			GUI::DrawLine(l_forearm, l_hand, clr, Wight, true);

			GUI::DrawLine(spine, r_upperarm, clr, Wight, true);
			GUI::DrawLine(r_upperarm, r_forearm, clr, Wight, true);
			GUI::DrawLine(r_forearm, r_hand, clr, Wight, true);
			GUI::DrawLine(spine, pelvis, clr, Wight, true);

			GUI::DrawLine(pelvis, l_hip, clr, Wight, true);
			GUI::DrawLine(l_hip, l_knee, clr, Wight, true);
			GUI::DrawLine(l_knee, l_foot, clr, Wight, true);
			GUI::DrawLine(pelvis, r_hip, clr, Wight, true);

			GUI::DrawLine(r_hip, r_knee, clr, Wight, true);
			GUI::DrawLine(r_knee, r_foot, clr, Wight, true);
			GUI::DrawLine(r_foot, r_toe, clr, Wight, true);
			GUI::DrawLine(l_foot, l_toe, clr, Wight, true);
		}

	}
}

_FI void Esp::DrawTarget(AimTarget Target)
{
	if (Target.Cur)
	{
		BasePlayer* playerTarget = Target.Cur;
		Color playerColor = Color(255, 255, 255, 255);

		/*for (int i = 0; i < 10; i++) {
			if (TargetIDList[i] != 0) {
				if (TargetIDList[i] == Target.Cur->GetSteamID()) {
					playerColor = Color(255, 0, 0, 255);
					playerTarget = (BasePlayer*)TargetList[i];
				}
				else
				{
					playerColor = Color(255, 255, 255, 255);
					playerTarget = Target.Cur;
				}
			}
			else if (TargetIDList[i] == 0)
			{
				playerColor = Color(255, 255, 255, 255);
				playerTarget = Target.Cur;
			}
		}*/


		if (Vars::Visuals::PlayerEsp::TargetLine) {
			Vector3 BonePos = playerTarget->GetBoneByID(head); Vector2 HeadPos;
			if (WorldToScreen(BonePos, HeadPos)) {
				GUI::DrawLine({ Vector2(Vars::ScreenWidth / 2, Vars::ScreenHeight / 2) }, { HeadPos.x,HeadPos.y }, playerColor, 1.2, true);
			}
		}
	}
}

class CornerBox
{
public:
	Vector3 left;
	Vector3 right;
	Vector3 top;
	Vector3 bottom;
	bool Valid = true;
	Color clr;
};

struct BoxBounds {
	float left, right, top, bottom;

	bool Empty() {
		if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
			return true;

		if (this->left == 0xFFFFFFFF || this->right == -0xFFFFFFFF || this->top == 0xFFFFFFFF || this->bottom == -0xFFFFFFFF)
			return true;

		return false;
	}
	static BoxBounds Null() {
		return { 0, 0, 0, 0 };
	}
};

inline void DrawFullBox(float CalcX, float CalcY, float CalcW, float CalcH, Color BoxColor, float Wight = 1.5)
{



	GUI::DrawLine({ CalcX, CalcY }, { CalcX + CalcW ,CalcY }, BoxColor, Wight, false);
	GUI::DrawLine({ CalcX, CalcX }, { CalcX, CalcY + CalcH }, BoxColor, Wight, false);
	/*GUI::DrawLine({ CalcX + CalcW, CalcY }, { (CalcX + CalcW) - CalcW,CalcY }, BoxColor, Wight, false);
	GUI::DrawLine({ CalcX + CalcW, CalcY }, { CalcX + CalcW,CalcY + CalcH }, BoxColor, Wight, false);*/

	// GUI::StartGlRender(render_type::boxoutline, { CalcX, CalcY }, { CalcW , CalcH }, BoxColor);
}

inline void DrawVertHealthBar(float CalcX, float CalcY, float CalcW, float CalcH, int health, int maxhealth, bool Npc) {

	const auto MaxHealth = (Npc ? maxhealth : 100);
	float Percentage = health * (CalcH / MaxHealth);

	GUI::StartGlRender(render_type::box, { CalcX - 6.2f, CalcY }, { 3.4f, CalcH }, { 0, 0, 0, 170 });
	GUI::StartGlRender(render_type::box, { CalcX - 6.2f, CalcY + CalcH - Percentage }, { 3.4f, Percentage }, { 0,255, 0,255 });
	GUI::StartGlRender(render_type::boxoutline, { CalcX - 6.2f, CalcY }, { 3.4f, CalcH }, { 0, 0, 0, 255 });

	wchar_t outputText[512];
	f_swprint(outputText, _(L"%d"), health);

	GUI::String({ CalcX - 13.4f, CalcY + CalcH - Percentage - 10, 20, 20 }, outputText, { 255,255,255,255 }, true, 9);
}

inline void DrawHorHealthBar(float CalcX, float CalcY, float CalcW, float CalcH, int health, int maxhealth, bool Npc) {

	const auto MaxHealth = (Npc ? maxhealth : 100);
	float Percentage = health * ((CalcW + 12.f) / MaxHealth);

	GUI::StartGlRender(render_type::box, { CalcX - 6.f, CalcY + CalcH + 2 }, { CalcW + 12.f, 3.2 }, { 0, 0, 0, 170 });
	GUI::StartGlRender(render_type::box, { CalcX - 5.8f, CalcY + CalcH + 2.2f }, { Percentage, 3 }, { 0,255, 0,255 });
	GUI::StartGlRender(render_type::boxoutline, { CalcX - 6.f, CalcY + CalcH + 2 }, { CalcW + 12.f, 3.2 }, { 0, 0, 0, 255 });
}

void DrawDefaultBox(float x, float y, float w, float h, float size, Color clr)
{
	GUI::set_color(clr.GetUnityColor());

	GUI::GuiMethods::DrawTexture(Rect(x, y, size, h + 1), g_WhiteTexture);
	GUI::GuiMethods::DrawTexture(Rect(x + w, y, size, h + 1), g_WhiteTexture);
	GUI::GuiMethods::DrawTexture(Rect(x, y, w + 1, size), g_WhiteTexture);
	GUI::GuiMethods::DrawTexture(Rect{ x, y + h, w + 1, size }, g_WhiteTexture);
}

inline void Esp::PlayerDraw(BasePlayer* Player, bool isNpc, bool isEnemy)
{
	if (!Player) return;

	const bool Visible = Unity::CheckLOS(EyePos, Player->GetBoneByID(head));

	const Color NameColor = Visible ? ColorPicker::TextEspVisible : ColorPicker::TextEspInVisible; // ColorPicker::WeaponVisible
	const Color WeaponColor = Visible ? ColorPicker::WeaponVisible : ColorPicker::WeaponInVisible; // ColorPicker::WeaponVisible
	const Color FlagsColor = Visible ? ColorPicker::FlagsVisible : ColorPicker::FlagsInVisible;
	const Color BoxColor = Visible ? ColorPicker::BoxVisible : ColorPicker::BoxInVisible;
	const Color SkeletonColor = isEnemy ? Color(255, 0, 0, 255) : Visible ? ColorPicker::SkeletonsVisible : ColorPicker::SkeletonsInVisible;
	// GUI::DrawLine({ 10,10 }, { 30,30 }, { 255,255,255,255 }, 3, true);
	DrawSkeleton(Player, SkeletonColor, 1.2f);

	BoxBounds ret = { 0xFFFFFFFF, -0xFFFFFFFF, 0xFFFFFFFF, -0xFFFFFFFF };

	const BoneList Bones[15] = {
		l_foot, l_knee, l_hip,
		r_foot, r_knee, r_hip,
		spine3, neck, head,
		l_upperarm, l_forearm, l_hand,
		r_upperarm, r_forearm, r_hand
	};

	CornerBox cornerBox;

	for (int j = 0; j < 15; j++)
	{
		auto currentBoneV3 = Player->GetTransform(BoneList(Bones[j]))->Position(); Vector2 bone_screen;
		if (Bones[j] == BoneList(head))
		{
			currentBoneV3.y += 0.2f;
		}
		else if (Bones[j] == BoneList(r_foot) || Bones[j] == BoneList(l_foot))
		{
			currentBoneV3.y -= 0.2f;
		}
		WorldToScreen(currentBoneV3, bone_screen);
		if (bone_screen.x < ret.left)
		{
			ret.left = bone_screen.x;
			cornerBox.left = currentBoneV3;
		}
		if (bone_screen.x > ret.right)
		{
			ret.right = bone_screen.x;
			cornerBox.right = currentBoneV3;
		}
		if (bone_screen.y < ret.top)
		{
			ret.top = bone_screen.y;
			cornerBox.top = currentBoneV3;
		}
		if (bone_screen.y > ret.bottom)
		{
			ret.bottom = bone_screen.y;
			cornerBox.bottom = currentBoneV3;
		}
	}

	if (ret.Empty()) cornerBox.Valid = false;

	if (cornerBox.Valid)
	{
		Vector2 bottom; Vector2 left; Vector2 top; Vector2 right;
		if (WorldToScreen(cornerBox.left, left) && WorldToScreen(cornerBox.right, right) && WorldToScreen(cornerBox.top, top) && WorldToScreen(cornerBox.bottom, bottom))
		{
			const auto x = left.x - 2;
			const auto y = top.y;

			const auto w = right.x - left.x + 4;
			const auto h = bottom.y - top.y;

			float CurPos = 0;
			float HealthPos = 0;
			float CurPos2 = 0;

			const auto Name = Player->GetName();
			const auto PlayerDist = (int)Maths::Calc3D_Dist(LocalPlayer->GetBoneByID(head), Player->GetBoneByID(head));
			// const ULONG64 TeamID = Player->TeamID();
			// ULONG64 TeamName = Player->GetSteamID();
			/*float cur_health = RV<float>(ply + Dump::BasePlayer::_health);
			float max_health = RV<float>(ply + Dump::BasePlayer::_maxHealth);
			float healthfromnone = cur_health / max_health;
			float bingbong_ = max(0.f, min(healthfromnone, 1));
			float num1 = 1 / 1;
			float bar_sync_ = bingbong_ * num1;*/

			if (Vars::Visuals::PlayerEsp::BoxEsp == 1) {
				/*GUI::StartGlRender(render_type::boxoutline, { x - 1, y - 1 }, { w + 2 , h + 2 }, { 0,0,0,170 });
				GUI::StartGlRender(render_type::boxoutline, { x + 1, y + 1 }, { w - 2 , h - 2 }, { 0,0,0,170 });
				GUI::StartGlRender(render_type::boxoutline, { x, y }, { w , h }, BoxColor);*/
				DrawDefaultBox(x - 1, y - 1, w + 2, h + 2, 1, { 0,0,0,170 });
				DrawDefaultBox(x + 1, y + 1, w - 2, h - 2, 1, { 0,0,0,170 });
				DrawDefaultBox( x,  y,  w,  h, 1, BoxColor);
			}
			// DrawFullBox(x, y, w, h, BoxColor);

			if (Vars::Visuals::PlayerEsp::BoxEsp == 2) {
				GUI::CornerBox(x, y, w, h, { 0,0,0,170 }, 3.6);
				GUI::CornerBox(x, y, w, h, BoxColor, 1.2);
			}
			if (Vars::Visuals::PlayerEsp::HealthEsp == 1)
				DrawVertHealthBar(x, y, w, h, Player->GetHealth(), Player->GetMaxHealth(), isNpc);

			if (Vars::Visuals::PlayerEsp::HealthEsp == 2)
			{
				DrawHorHealthBar(x, y, w, h, Player->GetHealth(), Player->GetMaxHealth(), isNpc);
				HealthPos += 5;
			}


			/*if (Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp)
			{
				wchar_t outputText[512];
				f_swprint(outputText, _(L"%s [%d]"), Name, PlayerDist);
				GUI::String({ x + (w / 2) - 200, y - 20, 400, 20 }, outputText, NameColor, true, Vars::EspTextSize);
			}
			if (!Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp) {
				wchar_t outputText[512];
				f_swprint(outputText, _(L"[%d]"), PlayerDist);
				GUI::String({ x + (w / 2) - 200, y - 20, 400 - CurPos2, 20 }, outputText, NameColor, true, Vars::EspTextSize);
			}*/
			wchar_t outputText[512];

			if (Vars::Visuals::PlayerEsp::NameEsp && !Vars::Visuals::PlayerEsp::DistanceEsp && !Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"%s"), Name);
			else if (!Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp && !Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"[%d]"), PlayerDist);
			else if (Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp && !Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"%s [%d]"), Name, PlayerDist);

			/*if (Vars::Visuals::PlayerEsp::NameEsp && !Vars::Visuals::PlayerEsp::DistanceEsp && Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"[Team: %s] %s"), TeamName, Name);
			else if (!Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp && Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"[Team: %s][%d]"), TeamName, PlayerDist);
			else if (Vars::Visuals::PlayerEsp::NameEsp && Vars::Visuals::PlayerEsp::DistanceEsp && Vars::Visuals::PlayerEsp::TeamID)
				f_swprint(outputText, _(L"[Team: %s] %s [%d]"), TeamName, Name, PlayerDist);*/

			if (Vars::Visuals::PlayerEsp::NameEsp || Vars::Visuals::PlayerEsp::DistanceEsp) {
				GUI::String({ x + (w / 2) - 200, y - 20, 400 - CurPos2, 20 }, outputText, NameColor, true, Vars::EspTextSize);
			}

			if (Vars::Visuals::PlayerEsp::WeaponEsp)
			{
				const auto ActWeapon = Player->GetActiveWeapon();
				const auto WeaponName = ActWeapon ? ActWeapon->GetWeaponName() : _(L"None");
				GUI::String({ x + (w / 2) - 200, y + h, 400, 20 }, WeaponName, WeaponColor, true, Vars::EspTextSize);
				CurPos += 15;
			}
			if (Vars::Visuals::PlayerEsp::ShowPlayerFlags)
			{
				const wchar_t* CurFlag = _(L"");

				if (Player->IsInSafeZone()) CurFlag = _(L"SafeZone");
				else if (Classes::get_mounted((DWORD64)Player)) CurFlag = _(L"Mounted");
				else if (Player->IsWounded()) CurFlag = _(L"Wounded");
				else if (Classes::IsOutside(Player) && !isNpc) CurFlag = _(L"IsOutside");
				else if (!Classes::IsOutside(Player) && !isNpc) CurFlag = _(L"InBase");

				// GUI::String({ middlePointPlayerFeet.x - 75, middlePointPlayerFeet.y + CurPos + HealthPos - 2, 150, 20 }, CurFlag, TextColor, true, 16);
				GUI::String({ x + (w / 2) - 200, y + h + CurPos + HealthPos - 2, 400, 20 }, CurFlag, FlagsColor, true, Vars::EspTextSize);
			}
		}

		if (Vars::Visuals::PlayerEsp::LookDirection)
		{
			Vector2 HeadPosV2;
			const  Vector3 HeadPosV3 = Player->GetBoneByID(head);
			Vector2 BodyForwardV2;
			const  Vector3 BodyForwardV3 = (Player->GetBoneByID(head) + (Player->GetEyes()->BodyForward()));
			if (WorldToScreen(BodyForwardV3, BodyForwardV2) && WorldToScreen(HeadPosV3, HeadPosV2))
				GUI::StartGlRender(render_type::line, Vector2::Zero2(), Vector2::Zero2(), { 255, 255, 255,255 }, Vector2::Zero2(), 0, HeadPosV2, BodyForwardV2);
		}

	}
}
