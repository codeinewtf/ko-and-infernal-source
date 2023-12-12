#pragma once

#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

// TODO
// 
// Fast Bow
// Minicopter Aim	
// Auto Collect
// Auto Upgrade
// Mass Suicide
// Zoom
// Chams Style Hands
// Spoof Hit Distance
// Show Target Icons
// Performance Ass
// 
// Fix Issues
//

Vector3 InitialVel;

class AimResult;
namespace Hooks
{
	auto VisUpdateUsingCulling = reinterpret_cast<void (*)(BasePlayer*, float, bool)>(0);
	auto ClientInput_Orig = reinterpret_cast<void (*)(BasePlayer*, InputState*)>(0);
	auto ProcessAttack_Orig = reinterpret_cast<void (*)(DWORD64, HitTest*)>(0);

	auto DoFixedUpdate_Orig = reinterpret_cast<void (*)(PlayerWalkMovement*, ModelState*)>(0);
	auto playerwalkmovement_client_input = reinterpret_cast<void (*)(PlayerWalkMovement*, DWORD64, ModelState*)>(0);
	auto OnLand = reinterpret_cast<void (*)(BasePlayer*, float)>(0);
	auto set_sprinting = reinterpret_cast<void (*)(ModelState*, bool)>(0);
	auto set_sleeping = reinterpret_cast<void (*)(ModelState*, bool)>(0);
	auto GetInheritedThrowVelocity_Orig = reinterpret_cast<Vector3(*)(BasePlayer*, Vector3)>(0);

	
	// OnViewmodelEvent
	auto OnViewmodelEvent_Orig = reinterpret_cast<void (*)(DWORD64, const char*)>(0);
	auto DoAttack_Orig = reinterpret_cast<void (*)(DWORD64)>(0);
	DWORD64 PlayerProjectileShoot_orig;
	DWORD64 PlayerProjectileUpdate_orig;
	DWORD64 PlayerProjectileRicochet_orig; // Strike
	auto OnAttacked = reinterpret_cast<void (*)(void*, HitInfo*)>(0);
	auto TryToMove = reinterpret_cast<void (*)(DWORD64)>(0);
	auto LaunchProjectile_Orig = reinterpret_cast<void(*)(DWORD64)>(0);
	auto ProjectileShoot_Orig = reinterpret_cast<void (*)(uint64_t, uint64_t)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("ProjectileShoot"), _("WriteToStream"), -1, _(""), _("ProtoBuf"))));
	//auto getmodifiedaimcone = reinterpret_cast<Vector3(*)(float, Vector3, bool)>(*reinterpret_cast<DWORD64*>(0));
	void InitHooks()
	{
		OnViewmodelEvent_Orig = reinterpret_cast<void (*)(DWORD64, const char*)>((DWORD64)(Il2cpp::Method(_("BaseMelee"), _("ProcessAttack"), 1, _(""), _(""))));
		ProcessAttack_Orig = reinterpret_cast<void (*)(DWORD64, HitTest*)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BaseMelee"), _("ProcessAttack"), 1, _(""), _(""))));

		ProjectileShoot_Orig = reinterpret_cast<void (*)(uint64_t, uint64_t)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("ProjectileShoot"), _("WriteToStream"), -1, _(""), _("ProtoBuf"))));
		DoAttack_Orig = reinterpret_cast<void (*)(DWORD64)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BaseProjectile"), _("DoAttack"), 0, _(""), _(""))));
		GetInheritedThrowVelocity_Orig = reinterpret_cast<Vector3(*)(BasePlayer*, Vector3)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BasePlayer"), _("GetInheritedThrowVelocity"), 0, _(""), _(""))));

		VisUpdateUsingCulling = reinterpret_cast<void (*)(BasePlayer*, float, bool)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BasePlayer"), _("VisUpdateUsingCulling"), -1, _(""), _(""))));
		LaunchProjectile_Orig = reinterpret_cast<void(*)(DWORD64)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BaseProjectile"), _("LaunchProjectile"), 0, _(""), _(""))));

		OnAttacked = reinterpret_cast<void (*)(void*, HitInfo*)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BasePlayer"), _("OnAttacked"), 1, _(""), _(""))));
		TryToMove = reinterpret_cast<void (*)(DWORD64)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("ItemIcon"), _("TryToMove"), -1, _(""), _(""))));
		playerwalkmovement_client_input = reinterpret_cast<void (*)(PlayerWalkMovement*, DWORD64, ModelState*)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("PlayerWalkMovement"), _("ClientInput"), -1, _(""), _(""))));
		OnLand = reinterpret_cast<void (*)(BasePlayer*, float)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BasePlayer"), _("OnLand"), 1, _("fVelocity"), _(""), 1)));
		ClientInput_Orig = reinterpret_cast<void (*)(BasePlayer*, InputState*)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("BasePlayer"), _("ClientInput"), -1, _(""), _(""))));
		DoFixedUpdate_Orig = reinterpret_cast<void (*)(PlayerWalkMovement*, ModelState*)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("PlayerWalkMovement"), _("DoFixedUpdate"), -1, _(""), _(""))));


		set_sprinting = reinterpret_cast<void (*)(ModelState*, bool)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("ModelState"), _("set_sprinting"), -1, _(""), _(""))));
		set_sleeping = reinterpret_cast<void (*)(ModelState*, bool)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("ModelState"), _("set_sleeping"), -1, _(""), _(""))));
		//getmodifiedaimcone = reinterpret_cast<Vector3(*)(float, Vector3, bool)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("AimConeUtil"), _("GetModifiedAimConeDirection"), 0, _(""), _(""))));
	}
}

void SimulateMovement()
{
	int Records = 32;
	Vector3 defaultVelocity = Classes::GetWorldVelocity(Target.Cur);
	if (defaultVelocity.Empty())
		defaultVelocity = Classes::GetWorldVelocity(Target.Cur);

	if (defaultVelocity.Empty())
	{
		PredictionData::PredictionDatas.currentVelocityRecords = 0;
		PredictionData::PredictionDatas.currentVelocityIndex = 0;
		PredictionData::PredictionDatas.avgVel = defaultVelocity;
	}
	else {
		PredictionData::PredictionDatas.velocities[PredictionData::PredictionDatas.currentVelocityIndex++] = defaultVelocity;
		if (PredictionData::PredictionDatas.currentVelocityIndex >= Records)
			PredictionData::PredictionDatas.currentVelocityIndex = 0;

		PredictionData::PredictionDatas.currentVelocityRecords++;
		if (PredictionData::PredictionDatas.currentVelocityRecords >= 0)
			PredictionData::PredictionDatas.currentVelocityRecords = Records;

		int currentRecords = PredictionData::PredictionDatas.currentVelocityRecords;

		Vector3 velSum{};
		for (size_t j = 0; j < currentRecords; j++)
			velSum += PredictionData::PredictionDatas.velocities[j];

		PredictionData::PredictionDatas.avgVel = velSum / (float)currentRecords;
	}
}


Vector3 MoveCircle(Vector3 position, Vector3 second_position, float value, bool negative) {

	if (value == 0) {
		position = position;
	}
	else {
		if (negative) {
			position -= second_position;
		}
		else {
			position += second_position;
		}
	}

	return position;
}
float deploy = 0.0;

void hk_DoFixedUpdate(PlayerWalkMovement* BaseMovement, ModelState* modelstate)
{
	//Vector3 vel = BaseMovement->TargetMovement();
	//float max_speed = (BaseMovement->Swimming() || BaseMovement->Ducking() > 0.5) ? 1.7f : 5.5f;
	//max_speed = max(max_speed, vel.Length());
	//if (Vars::Misc::OmniSprint) {
	//	float len = vel.Length();
	//	if (len > 0.f) {
	//		Vector3 target_vel = Vector3(vel.x / len * max_speed, vel.y, vel.z / len * max_speed);
	//		safe_write(BaseMovement + 0x34, target_vel, Vector3);
	//	}
	//}

	//if (Vars::Misc::WalkTo)
	//{
	//	Weapon* Held = LocalPlayer->GetActiveWeapon()->HeldEntity();
	//	if (Held)
	//	{
	//		AI::AutoWalkTo(BaseMovement, modelstate);
	//		//AI::AutoWalkTo2(BaseMovement, modelstate);
	//	}
	//}
	//else
	//	CanBhopJump = false;



	Hooks::DoFixedUpdate_Orig(BaseMovement, modelstate);
}



void hk_PlayerWalkMovement_ClientInput(PlayerWalkMovement* Movment, DWORD64 inputstate, ModelState* ModelState) {
	Hooks::playerwalkmovement_client_input(Movment, inputstate, ModelState);


	Hooks::set_sprinting(ModelState, true);
	//Hooks::set_sleeping(model_state, true);
	if (Vars::Misc::LockToPlayersHead && !(Vars::Misc::InteractiveDebug && Debugging)) {
		if (Target.Cur)
		{
			Vector3 Dir = (Target.Cur->GetEyes()->BodyForward());
			Vector3 LockPosition = Target.Pos + Vector3(-Dir.x, Dir.y - 0.2, -Dir.z);
			// Circle3D(Target.Cur->get_transform()->Position(), { 205.f, 100.f, 205.f, 255.f }, 2.5);
			if (Target.Distance < 2.5 && TeleportingToPlayersHead)
			{
				Classes::TeleportTo(Movment, LockPosition, LocalPlayer);
			}
		}
	}


	if (Vars::Misc::Jesus && LocalPlayer) {
		Vector3 vel = safe_read(Movment + O::BaseMovement::TargetMovementk__BackingField, Vector3);

		Vector3 local = LocalPlayer->GetBoneByID(BoneList::l_foot);

		typedef float(__stdcall* WD)(Vector3, bool, bool, BasePlayer*);

		float currentwater = ((WD)(g_Base + offsets::waterLevel))(local, true, false, LocalPlayer); // public static float GetWaterDepth(Vector3 pos, bool waves, bool volumes, BaseEntity forEntity) { }

		float upperwater = local.y - currentwater;
		upperwater -= 2.f;
		if (upperwater < 0.f && vel.y <= 0.1f) {
			vel.y = -upperwater;
		}
		safe_write(Movment + O::BaseMovement::TargetMovementk__BackingField, vel, Vector3);
	}
	/*if (inputstate) {
		auto WasJustPressed = reinterpret_cast<bool (*)(DWORD64, Button)>((DWORD64)(g_Base + 0x808EE0));
		if (WasJustPressed(inputstate, Button::JUMP))
		{
			Movment->DoJump(Movment, ModelState);
		}
	}*/
    /*safe_write(Movment + 0xd0, Unity::get_time() - 1, float);
	safe_write(Movment + 0xd4, Unity::get_time() + 1, float);
	safe_write(Movment + 0xcc, Unity::get_time(), float);*/

	// PlayerWalkMovement

	
	// maxStepHeight // 0x88
	/*safe_write(Movment + 0x98, 0, float);
	safe_write(Movment + 0x88, 0, float);*/ // jumping
	// safe_write(Movment + O::PlayerWalkMovement::jumping, true, bool);
	safe_write(Movment + O::BaseMovement::adminCheat, false, bool);

	if (Vars::Misc::SpiderManBypass) Movment->set_radius(0.44); else Movment->set_radius(0.5);

	// Movment->set_height(0.2);

	if (Vars::Exploits::Manipulation && Manipulating && Vars::Exploits::AutoStopOnManipulation) Movment->TargetMovement({ 0, 0, 0 });

	DeathBarrier::IsInsideTerrain(Vars::Misc::AntiInsideTerrain);
	IsFlying(Vars::Misc::AntiFlyKick, Movment);
	InteractiveFlyHack(Vars::Misc::InteractiveFly, Movment);
	ModelState->RemoveFlag(ModelState_Flag::Flying);

	if (Vars::Misc::OnLadder && OnLaddering) ModelState->SetFlag(ModelState_Flag::OnLadder);

	if (Vars::Misc::InteractiveDebug && Debugging) {

		ModelState->SetFlag(ModelState_Flag::Mounted);
		ModelState->SetFlag(ModelState_Flag::OnGround);
		safe_write((uint64_t)Movment + 0x4C, 1, float);
	}// Relaxed

	//	else
	//	{
	//		Write<float>((DWORD64)Movment + 0x68, 1.8f);
	//	}
	//	// Write<float>((DWORD64)Movment + 0x68, 5.5f);
	//	/*float hh = Read<float>((DWORD64)Movment + 0x68);
	//	CurHeaight = hh;*/
	//}
	//else
	//{
	//	Write<float>((DWORD64)Movment + 0x68, 1.8f);
	//}

	//if (Vars::Misc::Jesus && OnWater()) {
	//	safe_write(Movment + O::PlayerWalkMovement::flying, 1, bool);	// private bool flying;
	//	safe_write(Movment + O::PlayerWalkMovement::swimming, 0.f, float);	// private bool swimming;
	//	safe_write(Movment + O::PlayerWalkMovement::gravityMultiplierSwimming, 0, bool);	// private bool gravityMultiplierSwimming;
	//	safe_write(Movment + O::PlayerWalkMovement::gravityMultiplier, 0, bool);
	//}

	if (Vars::Misc::JumpShoot)
	{
		ModelState->SetFlag(ModelState_Flag::OnGround);
		safe_write((uint64_t)Movment + 0x4C, 1, float);
	}
	if (Vars::Misc::Bhop && Unity::GetKeyInt(32) || CanBhopJump) {
		static float b = 32.0f;
		if (b >= 32.0f) {
			float radius = LocalPlayer->GetRadius();
			float height = LocalPlayer->GetHeight(false);
			Vector3 vector = (LocalPlayer->lastSentTick()->position() + LocalPlayer->get_transform()->Position()) * 0.5f;
			float flyhack_extrusion = 0.25f;
			Vector3 vector2 = vector + Vector3(0.0f, radius - flyhack_extrusion, 0.0f);
			Vector3 vector3 = vector + Vector3(0.0f, height - radius, 0.0f);
			float radius2 = radius - 0.05f;
			bool isgrounded = Unity::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
			if (isgrounded) {
				Movment->Jump(ModelState);
				b = 0.0f;
			}
		}
		b++;
	}

	//Manipulation::ScanForTP();

	//if (Vars::Misc::tp_gotpath || Manipulation::teleport::found_path) {
	//	LocalPlayer->ClientTickInterval(0.05f); b  ,m
	//	for (int i = 0; i < 10; i++) {
	//		Classes::TeleportTo(Movment, Vars::Misc::to_path[i], LocalPlayer);
	//		LocalPlayer->ClientTickInterval(0.05f);
	//	}
	//	Vars::Misc::tp_gotpath = false;
	//}
}

namespace Mathx
{
	float Decrement(float flt)
	{
		auto Decrement = reinterpret_cast<float (*)(float)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("Mathx"), _("Decrement"), 1, _(""), _(""))));
		return Decrement(flt);
	}

	float Increment(float flt)
	{
		auto Increment = reinterpret_cast<float (*)(float)>(*reinterpret_cast<DWORD64*>(Il2cpp::Method(_("Mathx"), _("Increment"), 1, _(""), _(""))));
		return Increment(flt);
	}
};

void Launch(Projectile* pr, float initialDistance) {

	if (LocalPlayer && pr->owner()->GetSteamID() == LocalPlayer->GetSteamID()) {

		PrUpdate = pr;
		while (pr->IsAlive() && (pr->traveledDistance() < initialDistance || pr->traveledTime() < 0.1f))
		{
			Vector3 vector2 = pr->currentVelocity() * 0.03125;
			float magnitude = vector2.Magnitude();
			float num2 = 1.f / magnitude;
			Vector3 vector3 = vector2 * num2;
			Vector3 vector4 = pr->currentPosition() + vector3 * magnitude;
			RayLine line = RayLine(pr->currentPosition(), vector4);
			float ScanRange = Vars::Exploits::BulletTpExternded ? 6 : Vars::Exploits::BulletTpDist;

			Vector3 FirstNearest = line.ClosestPoint(Target.Pos);
			float DistanceToPoint1 = FirstNearest.Distance(Target.Pos);

			if (Vars::Exploits::BulletTp) {
				float ScanRange = Vars::Exploits::BulletTpDist;
				if (DistanceToPoint1 < ScanRange)
				//if (!Vars::Exploits::UknMeme && DistanceToPoint1 < 3)
				{
					UpdateVelocity(pr, 0.00025);
					BulletTeleport::TpBulletHitsP2(pr, FirstNearest, FirstNearest, 0);
				}
				else
				{
					UpdateVelocity(pr, 0.03125);
				}
			}
			else
			{
				UpdateVelocity(pr, 0.03125);
			}
		}
		
		float time = Unity::get_fixedTime();
		time -= pr->traveledTime();
		pr->launchTime(time);
	}
	else {
		return ProjectileLaunch(pr);
	}
}
bool CanAttack_hk(BaseProjectile* bp)
{
	return true;
}

bool CanAim_hk(BaseProjectile* bp)
{
	return true;
}

float GetMeleeDrag(int weaponID)
{
	switch (weaponID)
	{
	case 1326180354:
		return 0.5;
		break;
	case -1978999529:
		return 0.5;
		break;
	case 1090916276:
		return 0.5;
		break; // 1491189398
	case 1491189398:
		return 0.5;
		break; // paddle
	case -1137865085:
		return 0.5;
		break; // machete
	case -1966748496:
		return 0.5;
		break; // machete
	case 2040726127:
		return 0.5;
		break; // Combat Knife
	case 1814288539:
		return 0.5;
		break; // Костяной нож
	case -1469578201:
		return 0.5;
		break; // Костяной нож
	default:
		return 0.1;
		break;
	}
}

float GetMeleeGravity(int weaponID)
{
	switch (weaponID)
	{
	case 1540934679:
		return 2;
		break;
	case 1602646136:
		return 2;
		break;
	case 1090916276:
		return 2;
		break;
	case 1491189398:
		return 2;
		break;
	default:
		return 1;
		break;
	}
}

float ValidinitialDistance(Projectile* pr,float startVel, float initialDistance, float predictedTravelTime, float ShotTime) {

	float num21 = (initialDistance - 1) + (Vars::Exploits::DesyncTime * startVel);
	return num21;
}

//__forceinline inline static inline double inline returnValueIsPinlinerobably_TheMinlineaxDistanceForProjinlineectileInitialDistanceWithoutIinlinenvalidsBlessedByTimoxa1337inlinePleaseNoInvalidOrElseIWillinlinePasteFromKnowninlineLegitPlayersOnTwittinlineerPorsfinkteinliner(Projectile*** pr, float initialDistance, float predictedTravelTime) {
//	inline bool flag6 = true;
//	inline double num7 = predictedTravelTime;
//	inline double num8 = 2.f / 60.f;
//	inline double num9 = 2.f * Manipulation::Max(Unity::get_deltaTime(), Unity::get_smoothDeltaTime(), Unity::get_fixedDeltaTime());
//	inline double num10 = (Vars::Exploits::DesyncTime + num7 + num8 + num9) * 1.5f;
//	inline double magnitude1 = (**pr)->InitialVelocity().Magnitude();
//	inline double num14 = initialDistance + num10 * magnitude1;
//	inline bool flag7 = true;
//	inline double num15 = predictedTravelTime;
//	double num16 = 2.f / 60.f;
//	double magnitude2 = (**pr)->InitialVelocity().Magnitude();
//	double num17 = 2.f * Manipulation::Max(Unity::get_deltaTime(), Unity::get_smoothDeltaTime(), Unity::get_fixedDeltaTime());
//	double num19 = initialDistance + num10 * magnitude2;
//	double num18 = (Vars::Exploits::DesyncTime + num7 + num8 + num9) * 1.5f;
//	return num14 + num19 * flag6 * flag7 * 0.5;
//}

float lastProjectileVelocity;
void hook_PlayerProjectileShoot(int64_t rcx, int64_t rdx, int64_t r9, int64_t projectileShoot, int64_t arg5)
{
	typedef void(__stdcall* Orig)(int64_t, int64_t, int64_t, int64_t, int64_t);

	float time = Unity::get_fixedTime();
	float TravelTime = 0.f;
	int Simulations = 0;

	const auto Orig_Func = reinterpret_cast<void (*)(int64_t, int64_t, int64_t, int64_t, int64_t)>(Hooks::PlayerProjectileShoot_orig);

	if (!HeldEntity) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
	auto classname = HeldEntity->ClassName();
	if (!classname) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
	// BaseLauncher
	if (m_strcmp(classname, _("BaseLauncher"))) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);

	float SpreadPsilent = (Vars::Aim::pSilentSpread * 0.01);

	float initialDistance = 0;

	DWORD64 ShootList = *(DWORD64*)(*(DWORD64*)(projectileShoot + 0x18));
	if (!ShootList) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
	ShootList = *(DWORD64*)(*(DWORD64*)(projectileShoot + 0x18) + 0x10);
	auto Size = *(int*)(*(DWORD64*)(projectileShoot + 0x18) + 0x18);
	if (!Size) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
	Vector3 TargetPos, rpc_position;
	Vector3 Orig_Vel{};
	Vector3 AimVel = Vector3(0, 0, 0);
	Vector3 outPosition = Vector3(0, 0, 0);
	Projectile* p;
	if (!(m_strcmp(classname, _("BaseMelee"))) && !(m_strcmp(classname, _("Paddle"))) && !(m_strcmp(classname, _("Jackhammer"))))
	{
		isPredicted = true;
		bVel = Vector3();

		BaseProjectile* ProjectileList = Read<BaseProjectile*>(Read<DWORD64>((DWORD64)HeldEntity + 0x398) + 0x10);
		if (!ProjectileList) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);

		bool Predicted = true;

		if (Vars::Exploits::BehindWall && Manipulating && Vars::Exploits::Manipulation && Vars::Exploits::BahindWallType == 0 && Vars::Exploits::BehindWallPos != Vector3(0, 0, 0))
			TargetPos = Vars::Exploits::BehindWallPos;
		else { TargetPos = Target.Pos; }

		for (int i = 0; i < Size; i++) {

			DWORD64 ProjectileShoot = *(DWORD64*)(ShootList + 0x20 + i * 0x8);
			if (!ProjectileShoot) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
			Orig_Vel = Read<Vector3>(ProjectileShoot + 0x20);
			if (Orig_Vel == Vector3::Zero()) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
			lastProjectileVelocity = Orig_Vel.Length();
			rpc_position = Read<Vector3>(ProjectileShoot + 0x14);
			if (rpc_position == Vector3::Zero()) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
			InitialVel = Orig_Vel;
			BaseProjectile* projectile = Read<BaseProjectile*>(ShootList + 0x20 + i * 0x8);
			if (!projectile) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);

			p = *(Projectile**)((DWORD64)ProjectileList + 0x20 + i * 0x8);
			if (!p) return Orig_Func(rcx, rdx, r9, projectileShoot, arg5);
			Vector3 a;

			Vector3 EyePsoition = LocalPlayer->GetEyes()->EyePosition();
			Vector3 RealEyePsoition = LocalPlayer->GetEyes()->EyePosition();

			if (Vars::Exploits::Manipulation && Manipulating) {
				EyePsoition = EyePos;
			}
			else if (EyePsoition != RealEyePsoition)
			{
				EyePsoition = RealEyePsoition;
			}

			if (EyePsoition == Vector3::Zero()) return;

			//	Vector3 EyePsoition = EyePos;

			if (Vars::Exploits::Manipulation && Manipulating) {
				safe_write(projectile + 0x14, EyePos, Vector3);
			}
			outPosition = Read<Vector3>(ProjectileShoot + 0x14);
			Vector3 fakePos = Vector3::Zero();
			Vector3 AimPoint, AimPos;
			Vector3 OutputAngle, AimAngle;
			if (Vars::Aim::pSilent && Target.Cur)
			{
				if (PSilenting)
				{
					float HitChance = Maths::my_rand() % 100;
					if (Vars::Aim::HitChance <= HitChance)
						AimPoint = TargetPos;
					else AimPoint = TargetPos + Vector3(0, -2.1, 0);

					float IncBulletSpeed = 1;
					if (Vars::Weapon::ChangeVelScale && !(OverridingSpeed && Vars::Weapon::OVChangeVelScale)) IncBulletSpeed = Vars::Weapon::BulletSpeed; else if (Vars::Weapon::ChangeVelScale && OverridingSpeed && Vars::Weapon::OVChangeVelScale) IncBulletSpeed = Vars::Weapon::OVBulletSpeed; else IncBulletSpeed = 1;

					Vector3 StartPos = Read<Vector3>(ProjectileShoot + 0x14);
					float DistanceToTarget = Maths::Calc3D_Dist(EyePsoition, AimPoint);

					initialDistance = projectile->InitialDistance();

					Vector3 PredictedPoint = GetTrajectoryForEndPoint(AimPoint, EyePsoition, Orig_Vel.Length() * IncBulletSpeed, p->Drag(), p->gravityModifier(), initialDistance, &Predicted, &TravelTime);

					//if (Vars::Exploits::InstaHit) {

					//	initialDistance = initialDistanceValidation(p, Orig_Vel.Magnitude() * IncBulletSpeed, p->initialDistance(), TravelTime, time);

					//	if (initialDistance >= DistanceToTarget) {
					//		if (Vars::Exploits::BulletTp)
					//		{
					//			initialDistance = DistanceToTarget - Vars::Exploits::BulletTpDist;
					//		}
					//		else if (initialDistance >= DistanceToTarget)
					//		{
					//			initialDistance = DistanceToTarget;
					//		}
					//	}
					//}

					Vector3 PredictedPoint1337 = GetTrajectoryForEndPoint(AimPoint, StartPos, Orig_Vel.Length() * IncBulletSpeed, p->Drag(), p->gravityModifier(), initialDistance, &Predicted, &TravelTime);

					if (PredictedPoint1337 != Vector3::Zero())
					{
						AimPoint += PredictionData::PredictionDatas.avgVel * (TravelTime - (0.03125f * 2));
						bool EndPredict = false;
						Vector3 EndPoint = GetTrajectoryForEndPoint(AimPoint, StartPos, Orig_Vel.Length() * IncBulletSpeed, p->Drag(), p->gravityModifier(), initialDistance, &EndPredict, &TravelTime);
						Vector3 Direction = Classes::GetModifiedAimCone(SpreadPsilent, EndPoint - StartPos, false);

						AimVel = Direction.Normalized() * (Orig_Vel.Length() * IncBulletSpeed);

						if (EndPredict) {
							safe_write(projectile + 0x20, AimVel, Vector3);
						}
					}

					/*Vector3 angle = Classes::GetModifiedAimCone(SpreadPsilent, Target.Pos - EyePsoition, false);

					float yRad = DEG2RAD(angle.y);

					int currentIndex = 0;
					for (float pitch = 35.f; pitch <= 85.f; pitch += 2.f)
					{
						float pitchRad = DEG2RAD(pitch);

						Vector3 dir = {
							(float)(Maths::m_Sin(yRad) * Maths::m_Cos(pitchRad)),
							(float)Maths::m_Sin(pitchRad),
							(float)(Maths::m_Cos(yRad) * Maths::m_Cos(pitchRad))
						};

						float heightDiff = AimPos.y - EyePos.y;
						float dist2D = AimPos.DistanceXZ(EyePos);

						BulletDropPredictionData& predData = bulletDropData[currentIndex++];
						float idealSpeed = dist2D / predData.distCoeff;
						float yTravel = (predData.startY + (idealSpeed - 30.f) * predData.yCoeff);
						idealSpeed = Orig_Vel.Length() * 0.520;
						if (yTravel < heightDiff)
						{
							Vector3 end = L_GetEndPointForTrajectory(idealSpeed, pitch, p->Drag(), p->gravityModifier());
							if (end.Empty()) continue;
							if (end.Distance(AimPoint) > 20 ) continue;

							AimVel = Vector3(angle.x, dir.y, angle.z).Normalized() * idealSpeed;
							safe_write(projectile + 0x20, AimVel, Vector3);

						}
					}*/
				}
			}
		}

		for (int i = 0; i < ProjectileList->Size(); i++) {
			auto projectile = *(BaseProjectile**)((DWORD64)ProjectileList + 0x20 + i * 0x8);
			p = *(Projectile**)((DWORD64)ProjectileList + 0x20 + i * 0x8);

			if (!projectile) continue;

			// projectile->InitialDistance(initialDistance);

			ItemModProj* mod = projectile->GetItemModPr();
			if (mod)
			{
				Write<float>((DWORD64)mod + 0x30, 0);
				Write<float>((DWORD64)mod + 0x38, 0);
			}

			// projectile->InitialDistance(50);

			if (Vars::Aim::pSilent && Target.Cur) {
				if (Predicted && PSilenting) {
					projectile->CurrentVelocity(AimVel);
				}
			}

			//if (Vars::Visuals::BulletTraces)
			//{
			//	Classes::DDrawLine(projectile->CurrentPosition(), projectile->CurrentPosition() + ManipulationAngle, ColorPicker::BulletRGBBool ? RGBA(0.08f).GetUnityColor() : ColorPicker::BulletTracer.GetUnityColor(), 4, false, true);
			//} // HitPositionWorld

			if (Vars::Exploits::Manipulation && Manipulating) {
				projectile->GetTransform()->SetBonePos(EyePos);
				projectile->CurrentPosition(EyePos);
			}
			else {
				projectile->GetTransform()->SetBonePos(outPosition);
				projectile->CurrentPosition(outPosition);
			}


			Write<float>((DWORD64)projectile + 0x2c, Vars::Weapon::FatBulletValue);
			/*if (Vars::Weapon::FatBullet)
			{
				Write<float>((DWORD64)projectile + 0x2c, Vars::Weapon::FatBulletValue);
			}*/
			//Launch((Projectile* )projectile);
		}
		//} while (0);
	}
	isPredicted = false;

	Vars::Misc::fixed_time_last_shot = Unity::get_fixedTime();
	Vars::Misc::did_reload = false;
	Vars::Misc::just_shot = true;

	Orig_Func(rcx, rdx, r9, projectileShoot, arg5);//fixed

	if (!(m_strcmp(classname, _("BaseMelee"))) && !(m_strcmp(classname, _("Paddle"))) && !(m_strcmp(classname, _("Jackhammer"))))
	{
		BaseProjectile* ProjectileList = Read<BaseProjectile*>(Read<DWORD64>((DWORD64)HeldEntity + 0x398) + 0x10);
		for (int i = 0; i < ProjectileList->Size(); i++) {
			auto pr = *(Projectile**)((DWORD64)ProjectileList + 0x20 + i * 0x8);
			if (!pr) continue;

			Launch(pr, initialDistance);
		}

		typedef void(*ClearAllLists)(uintptr_t);
		uintptr_t _List = safe_read((uintptr_t)HeldEntity + 0x398, uintptr_t);
		((ClearAllLists)(g_Base + offsets::ClearObjectList))(_List); // System_Collections_Generic_List_object___Clear
		// Recreated::ClearObjectList(_List);
	}
}

class ItemIcon
{
public:
	bool queuedForLooting()
	{
		if (!this) return false;
		return safe_read(this + 0x128, bool);
	}

	void RunTimedAction()
	{
		if (!this) return;
		typedef void(__stdcall* RunTimedA)(DWORD64);
		((RunTimedA)(g_Base + offsets::o_RunTimedAction))((DWORD64)this);
	}
};

void hk_TryToMove(ItemIcon* instance) {
	if (!instance) return Hooks::TryToMove((DWORD64)instance);

	Hooks::TryToMove((DWORD64)instance);

	if (Vars::Misc::FastLoot)
	{
		if (instance->queuedForLooting())
		{
			instance->RunTimedAction();
		}
	}
}



void hook_PlayerProjectileAttack(int64_t rcx, int64_t rdx, int64_t r9, int64_t PlayerProjAttack, int64_t arg5) {
	typedef void(__stdcall* Orig)(int64_t, int64_t, int64_t, int64_t, int64_t);
	auto Held = HeldEntity; if (!Held) return ((Orig)(PlayerProjectileAttack_Orig))(rcx, rdx, r9, PlayerProjAttack, arg5);//fixed
	auto classname = Held->ClassName();
	if (m_strcmp(classname, _("BaseMelee")) || (m_strcmp(classname, _("Paddle")) || (m_strcmp(classname, _("Jackhammer")))))
		return ((Orig)(PlayerProjectileAttack_Orig))(rcx, rdx, r9, PlayerProjAttack, arg5);//fixed;
	if (!Target.Cur) return ((Orig)(PlayerProjectileAttack_Orig))(rcx, rdx, r9, PlayerProjAttack, arg5);//fixed;
	auto GetPPA = reinterpret_cast<PlayerProjectileAttack*>(PlayerProjAttack);
	auto& Attack = GetPPA->playerAttack->attack;
	

	//Attack->hitPositionWorld = Target.Pos;

	if (Vars::Visuals::BulletTraces)
	{
		Classes::DDrawLine(EyePos, Attack->hitPositionWorld, ColorPicker::BulletRGBBool ? RGBA(0.08f).GetUnityColor() : ColorPicker::BulletTracer.GetUnityColor(), 4, false, true);
	} // HitPositionWorld

	/*if (Vars::Exploits::BulletTp)
	{
		Projectile* projectile = PrUpdate;

		float Dist = Maths::Calc3D_Dist(projectile->currentPosition(), Target.Cur->GetEyes()->EyePosition());
		if (Dist <= Vars::Exploits::BulletTpDist)
		{
			if (projectile)
			{
				Attack->hitPositionWorld = projectile->currentPosition();
				Classes::DDrawLine(Attack->hitPositionWorld, projectile->currentPosition(), ColorPicker::BulletRGBBool ? RGBA(0.08f).GetUnityColor() : ColorPicker::BulletTracer.GetUnityColor(), 4, false, true);
			}
		}
	}*/

	//do
	//{
	//	if (!Vars::Exploits::Pierce && !Vars::Exploits::ShootThroughTeammates) break;

	//	if (!LocalPlayer || Target.Heli || Target.Turret)
	//		break;

	//	Projectile* projectile = (Projectile*)lastProjectile;
	//	if (projectile)
	//	{
	//		auto HitTest = projectile->get_hit_test();
	//		if (HitTest)
	//		{
	//			auto GameObject = HitTest->get_GameObject();
	//			if (GameObject != 0)
	//			{
	//				bool canIgnore = Unity::CheckLOS(projectile->currentPosition(), Target.Pos, 0.18, 10551296);
	//				if (canIgnore)
	//				{
	//					auto layer = HitTest->get_GameObject()->get_layer();
	//					if (Vars::Exploits::Pierce)
	//					{
	//						if (layer != layer::Player_Server)
	//						{
	//							projectile->Integrity(1);
	//							safe_write(projectile + O::Projectile::invisible, false, bool);
	//							return;
	//						}
	//					}
	//					if (Vars::Exploits::ShootThroughTeammates && Target.IsTeammate)
	//					{
	//						if (layer == layer::Player_Server)
	//						{
	//							projectile->Integrity(1);
	//							safe_write(projectile + O::Projectile::invisible, false, bool);
	//							return;
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}

	//} while (0);

	do {
		if (!LocalPlayer)
			break;

		//Attack->hitMaterialID = 432631845;
		if (!Target.Cur)
			break;

		//Vars::prp = Attack->hitMaterialID;

		if (!Vars::Exploits::HeliOverride && Vars::Exploits::PlayerOverride == 0)
			break;

		if (Target.Cur)
		{
			if (!Target.Heli && Vars::Exploits::PlayerOverride != 0 && !Target.Turret) {
				if (Vars::Exploits::PlayerOverride != 0)
				{
					if (Vars::Exploits::PlayerOverride == 1)
					{
						Attack->hitBone = 698017942;
						Attack->hitPartID = 2173623152;
					}

					else if (Vars::Exploits::PlayerOverride == 2)
					{
						Attack->hitBone = 3901657145;
						Attack->hitPartID = 1750816991;
					}
					else if (Vars::Exploits::PlayerOverride == 3)
					{
						switch (Maths::my_rand() % 4) {
						case 0: // Body
							Attack->hitBone = 3901657145;
							Attack->hitPartID = 1750816991;
							break;
						case 1: // Legs
							Attack->hitBone = 3892428003;
							Attack->hitPartID = 1750816991;
							break;
						case 2: // LHand
							Attack->hitBone = 182688154;
							Attack->hitPartID = 1750816991;
							break;
						case 3: // RHand
							Attack->hitBone = 102231371;
							Attack->hitPartID = 1750816991;
							break;
						}
					}
					else if (Vars::Exploits::PlayerOverride == 4)
					{
						switch (Maths::my_rand() % 5) {
						case 0: // Body
							Attack->hitBone = 3901657145;
							Attack->hitPartID = 1750816991;
							break;
						case 1: // Legs
							Attack->hitBone = 3892428003;
							Attack->hitPartID = 1750816991;
							break;
						case 2: // LHand
							Attack->hitBone = 182688154;
							Attack->hitPartID = 1750816991;
							break;
						case 3: // RHand
							Attack->hitBone = 102231371;
							Attack->hitPartID = 1750816991;
							break;
						case 4: // RHand
							Attack->hitBone = 698017942;
							Attack->hitPartID = 2173623152;
							break;
						}
					}
				}
			}
			else if (Target.Heli && !Target.Turret) {


				auto weakspots = Target.Cur->WeakSpots();
				if (!weakspots)
					break;

				//if (!Vars::Exploits::HeliOverride) break;

				if (Target.Cur->GetHealth() <= 5000.0f)
				{
					Attack->hitBone = 2699525250;
					Attack->hitPartID = 2306822461;
				}
				else
				{
					Attack->hitBone = 224139191;
					Attack->hitPartID = 2306822461;
				}

			}
		}
	} while (0);

	//do
	//{
	//	if (!LocalPlayer)
	//		break;

	//	//Attack->hitMaterialID = 432631845;
	//	if (!Target.Cur)
	//		break;

	//	if (Attack)
	//	{
	//		if (PlayerTrans)
	//		{
	//			Attack->pointStart = newPosition;
	//			Attack->pointEnd = newPosition + (PlayerTrans->Position() - newPosition) * max(num19 - 1, 0);
	//			Attack->hitID = Target.Cur->GetNet()->GetID();
	//			Attack->hitBone = boneId;
	//			Attack->hitPartID = hitTest->HitPart();
	//			Attack->hitPositionWorld = newPosition;
	//			Attack->hitPositionLocal = InverseTransformPoint(PlayerTrans, newPosition);
	//			Attack->hitNormalWorld = Vector3(0, 0, 0);
	//			Attack->hitNormalLocal = Vector3(0, 0, 0);
	//		}
	//	}
	//
	//} while (0);

	// 432631845

	// Attack->hitMaterialID = 432631845;

	//if (Vars::Exploits::BulletTp) {
	//	Attack->hitPositionWorld = Vector3::MoveTowards(Attack->hitPositionWorld, Target.Cur->GetBoneByID(head), 0.1f);
	//	Attack->hitPartID = 16144115;
	//	Attack->hitBone = 698017942;
	//	Attack->hitID = Target.Cur->GetNet()->GetID();
	//}

	return ((Orig)(PlayerProjectileAttack_Orig))(rcx, rdx, r9, PlayerProjAttack, arg5);
}

DWORD64 DoFixedUpd, PlayerWM, PlayerPS, PrShoot, hkAttack, InheritedThrowVel;
DWORD64 WriteToStreamOrig = 0;
DWORD64 HKBlockJump;
DWORD64 BaseMovement_BlockJump;

void OnAtttackedHook(void* pacan, HitInfo* hitinfo)
{
	//if (!Target.Heli && !Target.Turret)
	//{
	//	/*Classes::DDrawText((DWORD64)Il2cpp::new_string(_("Test")), hitinfo->HitPositionWorld(), {0,255,0,255}, 5);*/
	//	/*wchar_t outputText[512];
	//	f_swprint(outputText, _(L"%d"), hitinfo->ProjectileDistance());
	//	LocalPlayer->ConsoleMsg(outputText);*/

	//	if (Vars::Weapon::CustomHitMat)
	//		hitinfo->HitMaterial(432631845);

	//	if (Vars::Visuals::HitMarker)
	//		Classes::DDrawSphereGizmo(hitinfo->HitPositionWorld(), 0.2, { 0,255,0,255 }, 4, false, false);

	//	if (Vars::Misc::HitSound)
	//		m_PlaySound(reinterpret_cast<LPCUTSTR>(_("C:\\HitSound\\hit.wav")), NULL, SND_FILENAME | SND_ASYNC);
	//}
	//if (!Vars::Misc::HitSound)
		Hooks::OnAttacked(pacan, hitinfo);

	ProjectileAttackInited = true;
}

DWORD64 mvitem;

DWORD64 Rainbow = NULL;

int HandChamUpd = 0;
int HandChamUpdRate = 100;
void HandChams()
{
	//if (Vars::Visuals::PlayerEsp::HandChams || Vars::Visuals::PlayerEsp::WeaponChams)
	//{
	//	if (!HeldEntity) return;
	//	if (HeldEntity->timeSinceDeploy() > HeldEntity->DeployDelay()) return;

	//	// if (Unity::ChamsShader)
	//	{
	//		int Chamsdsjdaisd = 0;
	//		static bool CanSet = false;
	//		static bool DidSet = false;
	//		auto model = Classes::get_ActiveModel();

	//		if (model) {
	//			CanSet = true;
	//			auto render = Unity::GetComponentsInChildren((DWORD64)model, Il2cpp::TypeGetObject(_("UnityEngine"), _("Renderer")));
	//			if (render) {
	//				auto size = safe_read(render + 0x18, DWORD64);
	//				for (int i = 0; i < size; i++) {
	//					auto renderer = safe_read(render + 0x20 + (i * 0x8), DWORD64);
	//					if (renderer) {
	//						Material* material = (Material*)Classes::get_material(renderer);
	//						if (material) {
	//							//if (!MainHandShader)
	//							//	MainHandShader = Unity::LoadAsset(Unity::ChamsShader, _(L"hologram.shader"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Shader")));//
	//							static DWORD64 chamsMat1 = 0;
	//							static DWORD64 chamsMat2 = 0;
	//							
	//							if (!Unity::CanOverWriteAssets ) {

	//								if (Vars::Visuals::PlayerEsp::WeaponChams || Vars::Visuals::PlayerEsp::HandChams)
	//								{
	//									if (!material->name()->Contains(_(L"fumes")) && !material->name()->Contains(_(L"flash")) && !material->name()->Contains(_(L"holosight")))
	//									{
	//										if (!material->name()->Contains(_(L"Arm")) && !material->name()->Contains(_(L"hoodie")) && !material->name()->Contains(_(L"Glove")) && !material->name()->Contains(_(L"Hand")) && !material->name()->Contains(_(L"Suit")) && !material->name()->Contains(_(L"Hand")) && !material->name()->Contains(_(L"tshirt")) && !material->name()->Contains(_(L"hazmat")) && !material->name()->Contains(_(L"torso")))
	//										{
	//											/*if (Vars::Visuals::PlayerEsp::WeaponChams)
	//											{
	//												Classes::set_shader((DWORD64)material, Galaxymaterial);
	//												GUI::SetInt((DWORD64)material, _(L"_holocount"), 0);
	//												Classes::SetColor((DWORD64)material, _(L"_VisCol"), ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams.GetUnityColor());
	//												Classes::SetColor((DWORD64)material, _(L"_InvisCol"), ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams2.GetUnityColor());
	//											}*/
	//											if (Vars::Visuals::PlayerEsp::WeaponChams) {
	//												switch (Vars::Visuals::PlayerEsp::HandChamsType)
	//												{
	//												case 0:
	//													if (StormShader != Classes::get_material((DWORD64)renderer)) {
	//														Unity::set_material(renderer, StormShader);
	//														chamsMat2 = Classes::get_material((DWORD64)renderer);
	//														// GUI::SetInt((DWORD64)chamsMat2, _(L"rainbow_go"), 0);
	//													}
	//													break;
	//												case 1: // GalaxyPink
	//													if (GalaxyPink != Classes::get_material((DWORD64)renderer)) {
	//														Unity::set_material(renderer, GalaxyPink);
	//													}
	//													break;
	//												case 2:
	//													if (GalaxyGreen != Classes::get_material((DWORD64)renderer)) {
	//														Unity::set_material(renderer, GalaxyGreen);
	//													}
	//													break;
	//												case 3:
	//													if (GalaxyRed != Classes::get_material((DWORD64)renderer)) {
	//														Unity::set_material(renderer, GalaxyRed);
	//													}
	//													break;
	//												case 4:
	//													if (GalaxyBlue != Classes::get_material((DWORD64)renderer)) {
	//														Unity::set_material(renderer, GalaxyBlue);
	//													}
	//													break;
	//												}
	//											}
	//										}
	//										else if (Vars::Visuals::PlayerEsp::HandChams)
	//										{
	//											switch (Vars::Visuals::PlayerEsp::HandChamsType)
	//											{
	//											case 0:
	//												if (StormShader != Classes::get_material((DWORD64)renderer)) {
	//													Unity::set_material(renderer, StormShader);
	//													chamsMat2 = Classes::get_material((DWORD64)renderer);
	//													// GUI::SetInt((DWORD64)chamsMat2, _(L"rainbow_go"), 0);
	//												}
	//												break;
	//											case 1: // GalaxyPink
	//												if (GalaxyPink != Classes::get_material((DWORD64)renderer)) {
	//													Unity::set_material(renderer, GalaxyPink);
	//												}
	//												break;
	//											case 2:
	//												if (GalaxyGreen != Classes::get_material((DWORD64)renderer)) {
	//													Unity::set_material(renderer, GalaxyGreen);
	//												}
	//												break;
	//											case 3:
	//												if (GalaxyRed != Classes::get_material((DWORD64)renderer)) {
	//													Unity::set_material(renderer, GalaxyRed);
	//												}
	//												break;
	//											case 4:
	//												if (GalaxyBlue != Classes::get_material((DWORD64)renderer)) {
	//													Unity::set_material(renderer, GalaxyBlue);
	//												}
	//												break;
	//											}
	//										}
	//									}
	//								}
	//							}
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//}
}
void(*WriteToStream)(uint64_t, uint64_t) = NULL;

//Classes::set_shader((DWORD64)material, Rainbow);
//Classes::SetColor((DWORD64)material, _(L"_RimColor"), ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams2.GetUnityColor());

//GUI::SetInt((DWORD64)material, _(L"_Brightness"), 1);
//GUI::SetInt((DWORD64)material, _(L"_RimPower"), 5); // _GlowTiling
//GUI::SetInt((DWORD64)material, _(L"_GlowTiling"), 1);
//GUI::SetInt((DWORD64)material, _(L"_GlowSpeed"), 5);

//GUI::SetInt((DWORD64)material, _(L"_ScanTiling"), 5);
//GUI::SetInt((DWORD64)material, _(L"_ScanSpeed"), 2);

//GUI::SetInt((DWORD64)material, _(L"_GlitchSpeed"), 10);
//GUI::SetInt((DWORD64)material, _(L"_GlitchIntensity"), 2);

//GUI::SetInt((DWORD64)material, _(L"_FlickerSpeed"), 50);
//Classes::SetColor((DWORD64)material, _(L"_MainColor"), ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams.GetUnityColor()); // ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams.GetUnityColor()
//Classes::SetColor((DWORD64)material, _(L"_RimColor"), ColorPicker::HandChamsRGBBool ? RGBA().GetUnityColor() : ColorPicker::HandChams2.GetUnityColor());
void LaunchProjectile_hk(DWORD baseProjectile)
{

	if (!baseProjectile) return;


	Hooks::LaunchProjectile_Orig(baseProjectile);

	Weapon* Held = HeldEntity;
	if (!Held) return;
	BaseProjectile* ProjectileList = Read<BaseProjectile*>(Read<DWORD64>((DWORD64)Held + 0x398) + 0x10);
	if (!ProjectileList) return;

	for (int i = 0; i < ProjectileList->Size(); i++) {
		auto pr = *(Projectile**)((DWORD64)ProjectileList + 0x20 + i * 0x8);

		if (!pr) continue;

		// Launch(pr);
	}

}
//int StoredStone111 = 0;
float LastPickUp = 0.0;
int LoopValue = 0;
int LoopUpdateRate = 100;
bool FindObjects = false;

void hook_PlayerProjectileUpdate(int64_t rcx, int64_t rdx, int64_t r9, int64_t PlayerProjUpdate, int64_t arg5)
{
	typedef void(__stdcall* Orig)(int64_t, int64_t, int64_t, int64_t, int64_t);

	auto ppu = reinterpret_cast<PlayerProjectileUpdate*>(PlayerProjUpdate);
	// auto& ppu = GetPPA;
	//FakeUpdate = (UINT64)ppu;
	// if (!FakeUpdate) FakeUpdate = (UINT64)ppu;

	return ((Orig)(Hooks::PlayerProjectileUpdate_orig))(rcx, rdx, r9, PlayerProjUpdate, arg5);
}

//public int projectileID; // 0x10
//public Vector3 hitPosition; // 0x14
//public Vector3 inVelocity; // 0x20
//public Vector3 outVelocity; // 0x2C
//public Vector3 hitNormal; // 0x38
//public float travelTime; // 0x44
//public bool ShouldPool; // 0x48
//private bool _disposed; // 0x49

class PlayerProjectileRicochet {
public:
	union {
		OFFSET(int, projectileID, 0x10);
		OFFSET(Vector3, hitPosition, 0x14);
		OFFSET(Vector3, inVelocity, 0x20);
		OFFSET(Vector3, outVelocity, 0x2C);
		OFFSET(Vector3, hitNormal, 0x38);
		OFFSET(float, travelTime, 0x44);
	};
};

void hook_PlayerProjectileRicochet(int64_t rcx, int64_t rdx, int64_t r9, int64_t playerProjectileRicochet, int64_t arg5)
{
	typedef void(__stdcall* Orig)(int64_t, int64_t, int64_t, int64_t, int64_t);
	auto projectileRicochet = reinterpret_cast<PlayerProjectileRicochet*>(playerProjectileRicochet);

	if (!Target.Cur) return ((Orig)(Hooks::PlayerProjectileRicochet_orig))(rcx, rdx, r9, playerProjectileRicochet, arg5);//fixed;

	Projectile* projectile = PrUpdate;
	if (projectile)
	{
		projectileRicochet->projectileID = projectile->projectileID();
		projectileRicochet->hitPosition = projectile->currentPosition();
		projectileRicochet->hitNormal = Vector3::Zero();
		projectileRicochet->travelTime = projectile->traveledTime();
		projectileRicochet->inVelocity = projectile->currentVelocity();

		Vector3 Direction = Classes::GetModifiedAimCone(0, Target.Pos - EyePos, false);
		Vector3 outVelocity = Direction.Normalized() * (projectile->currentVelocity().Length());

		projectileRicochet->outVelocity = outVelocity;
		projectile->currentVelocity(outVelocity);
		projectile->currentPosition(projectile->currentPosition() + projectile->currentVelocity().Normalized() * 0.001f);
		projectile->Integrity(1);
		((Orig)(Hooks::PlayerProjectileRicochet_orig))(rcx, rdx, r9, playerProjectileRicochet, arg5);

		Classes::DDrawSphere(projectileRicochet->hitPosition, 0.5, { 255,255,255,255 }, 5, false);
		return;
	}

	
}

void ProcessAttack_hk(DWORD64 melee, HitTest* hitTest)
{
	//if (!melee || !hitTest) return;

	//if (entity->GetName() == STATIC_CRC32("TreeEntity")) {
	if (Vars::Misc::AlwaysHotSpot)
	{

		AimResult OreEntity = AimResult::get_closest_object(LocalPlayer->GetTransform(47)->Position(), _(""), Vector3::Zero(), Vector3::Zero(), Vector3::Zero(), true, _("OreResourceEntity"));
		AimResult TreeEntity = AimResult::get_closest_object(LocalPlayer->GetTransform(47)->Position(), _(""), Vector3::Zero(), Vector3::Zero(), Vector3::Zero(), true, _("TreeEntity"));

		if (TreeEntity.valid && TreeEntity.dist <= 3 && TreeEntity.dist < OreEntity.dist)
		{
			AimResult TreeMarker = AimResult::get_closest_object(LocalPlayer->GetTransform(47)->Position(), _(""), Vector3::Zero(), Vector3::Zero(), Vector3::Zero(), true, _("TreeMarker"));
			if (TreeMarker.valid && TreeMarker.dist <= 3)
			{
				TreeEntity = TreeMarker; // hitTest->HitTest_HitMaterial((Str*)Il2cpp::new_string("glass"));
				hitTest->HitTransform(TreeEntity.entity->get_transform());
				hitTest->HitPoint(InverseTransformPoint(TreeEntity.entity->get_transform(), TreeEntity.entity->get_transform()->Position()));
				hitTest->HitTest_HitMaterial((Str*)Il2cpp::new_string(_("wood")));
			}
		}

		if (OreEntity.valid && OreEntity.dist <= 3 && OreEntity.dist < TreeEntity.dist)
		{
			AimResult OreHotSpot = AimResult::get_closest_object(LocalPlayer->GetTransform(47)->Position(), _(""), Vector3::Zero(), Vector3::Zero(), Vector3::Zero(), true, _("OreHotSpot"));
			if (OreHotSpot.valid && OreHotSpot.dist <= 3)
			{
				OreEntity = OreHotSpot;
				hitTest->HitTransform(OreEntity.entity->get_transform());
				hitTest->HitPoint(InverseTransformPoint(OreEntity.entity->get_transform(), OreEntity.entity->get_transform()->Position()));
			}
		}
	}
	//	if (Vars::Misc::HammerSpam) {
	//		if (HeldEntity) {
	//			if (ActiveWeapon->GetID() == 200773292) {
	//				BasePlayer* selectedEntity = Vars::Misc::HammerSpamMode == 0 ? LocalPlayer : Target.Cur;
	//				Vector3 HeadPos = selectedEntity->GetBoneByID(head);

	//				hitTest->HitTransform(selectedEntity->GetTransform(47));
	//				hitTest->AttackRay(Ray(LocalPlayer->GetEyes()->EyePosition(), HeadPos));
	//				hitTest->DidHit(true);
	//				hitTest->HitEntity(selectedEntity);
	//				hitTest->HitPoint(InverseTransformPoint(selectedEntity->GetTransform(47), HeadPos));
	//				hitTest->HitNormal(InverseTransformDirection(selectedEntity->GetTransform(47), HeadPos));
	//				hitTest->DamageProperties(reinterpret_cast<Weapon*>( melee )->DamageProperties());
	//				

	//				// HammerSpam(selectedEntity, HeadPos, HeldEntity, HeadPos + selectedEntity->GetEyes()->EyePosition());
	//			}
	//		}
	//	}
	//}
	// hitTest->HitTest_HitMaterial((Str*)Il2cpp::new_string(_("glass")));
	//if (!hitTest) {
	//	hitTest = (HitTest*)Il2cpp::object_new(Il2cpp::InitClass(_("HitTest"), _("")));
	//}

	//if (Target.Cur)
	//{
	//	/*HitTest* test = proj->hitTest;
	//	test->hitTransform = hitTransform;
	//	test->hitEntity = projInfo.targetEnt;
	//	test->attackRay.origin = hitInfo.point;
	//	test->attackRay.direction = projDirection.Normalized();
	//	test->hitPoint = hitTransform->InverseTransformPoint(headPoint);
	//	test->hitNormal = Vector3(0.f, 0.f, 0.f);
	//	test->didHit = true;
	//	test->hitDistance = dist;
	//	test->maxDistance = 999.f;
	//	proj->DoHit(test, headPoint, Vector3(0.f, 0.f, 0.f));*/
	//	Transform* hitTransform = Target.Cur->GetTransform(47);
	//	hitTest->HitTransform(hitTransform);
	//	hitTest->HitEntity(Target.Cur);
	//	hitTest->AttackRay(Ray(EyePos,(Target.Pos - EyePos).Normalized()));
	//	hitTest->HitPart(2173623152);
	//	hitTest->HitPoint(InverseTransformPoint(hitTransform, Target.Pos));
	//	hitTest->HitNormal({0,0,0});
	//	hitTest->DidHit(true);
	//	hitTest->MaxDistance(999);
	//}

	return Hooks::ProcessAttack_Orig(melee, hitTest);


}

void GetHeldEntity(BasePlayer* player)
{
	BaseProjectile* get_ActiveWeapon = player->GetActiveWeapon();
	if (get_ActiveWeapon)
	{
		ActiveWeapon = get_ActiveWeapon;
		HeldEntity = ActiveWeapon->HeldEntity();
	}
	else
	{
		ActiveWeapon = 0;
		HeldEntity = 0;
	}
}

BasePlayer* PlayerList[256];

void StoringEspLoop() {
	int ListSize = sizeof(EspObjects) / sizeof(EspObjects[0]);

	for (int i = 0; i < ListSize; i++) {

	}
}

void hk_BlockJump(float duration)
{
	reinterpret_cast<void (*)(float)>(HKBlockJump)(0);
} // BaseMovement_BlockJump

void hk_BaseMovement_BlockJump(float duration)
{
	reinterpret_cast<void (*)(float)>(BaseMovement_BlockJump)(0);
}

//v1 = (__int64(__fastcall*)(__int64))sub_1802B77F0("UnityEngine.Component::get_transform()");
//qword_18315A210 = (__int64)v1;

#define CALLED_BY(func,off) (reinterpret_cast<std::uint64_t>(_ReturnAddress()) > func && reinterpret_cast<std::uint64_t>(_ReturnAddress()) < func + off)

DWORD64 get_fixedTime_orig, get_trans_orig, get_run_orig;
bool cokksdf = false;



void MeleeAimBot(Projectile* pr)
{
	if (Vars::Exploits::MeleePsilent)
	{
		if (!Target.Cur) return;

		Vector3 EyePsoition = LocalPlayer->GetEyes()->EyePosition();
		Vector3 RealEyePsoition = LocalPlayer->GetEyes()->EyePosition();

		if (Vars::Exploits::Manipulation && Manipulating) {
			EyePsoition += ManipulationAngle;
		}
		else if (EyePsoition != RealEyePsoition)
		{
			EyePsoition = RealEyePsoition;
		}

		float TravelTime = 0;
		Vector3 aimVel;
		bool didPredict = false;

		Vector3 origVel = Read<Vector3>((DWORD64)pr + O::Projectile::initialVelocity);

		Vector3 EndPoint = GetTrajectoryForEndPoint(Target.Pos, EyePsoition, origVel.Length() * 1.5f, pr->Drag(), pr->gravityModifier(), 0, &didPredict, &TravelTime);
		EndPoint += (PredictionData::PredictionDatas.avgVel) * TravelTime;
		Vector3 Direction = Classes::GetModifiedAimCone(0, EndPoint - EyePsoition, false);

		aimVel = Direction.Normalized() * (origVel.Length() * 1.5f);

		// pr->initialDistance(50);

		Write<Vector3>((DWORD64)pr + O::Projectile::initialVelocity, aimVel);
		Write<Vector3>((DWORD64)pr + O::Projectile::currentVelocity, aimVel);
		pr->get_transform()->SetBonePos(EyePsoition);
		pr->currentPosition(EyePsoition);
		/*if (isPredicted)
		{
			if (bVel != Vector3::Zero())
			{
				pr->currentVelocity(bVel);
				pr->get_transform()->SetBonePos(EyePsoition);
				pr->currentPosition(EyePsoition);
			}
		}
		else
		{
			bVel = Vector3();
		}*/
	}
}

float hk_getFixedTime() {
	// public void InitializeVelocity(Vector3 overrideVel) { }
	if (CALLED_BY(g_Base + 0x709670 , 0x100)) {
		Projectile* pr = reinterpret_cast<Projectile*>(lastProjectile);
		if (pr) {
			Weapon* Held = HeldEntity; 
			if (Held && get_isAlive(pr) && get_isAuthoritative(pr)) {
				auto classname = Held->ClassName();
				if (m_strcmp(classname, _("BaseMelee")) || (m_strcmp(classname, _("Paddle")) || (m_strcmp(classname, _("Jackhammer"))))) {
					MeleeAimBot(pr);
				}
			}
		}
	}

	return reinterpret_cast<float(*)()>(get_fixedTime_orig)();
}

char* hk_Run() {
	// public void InitializeVelocity(Vector3 overrideVel) { }

	return _("assets/bundled/prefabs/fx/")/*reinterpret_cast<float(*)()>(get_fixedTime_orig)()*/;
}

__int64 hk_get_transform(__int64 a1) {
	// public void InitializeVelocity(Vector3 overrideVel) { }
	if (CALLED_BY(g_Base + 0x709670, 0x100)) {
		Projectile* pr = reinterpret_cast<Projectile*>(a1);
		if (get_isAlive(pr) && get_isAuthoritative(pr)) {
			lastProjectile = a1;
		}
	}

	return reinterpret_cast<__int64(*)(__int64)>(get_trans_orig)(a1);
}


DWORD64 HookedProjShoot;
void hk_ClientInput(BasePlayer* baseplayer, InputState* state) {
	if (!DoAttackhk)
		DoAttackhk = Virtual_Hook(_("BaseProjectile"), _("DoAttack"), &hk_DoAttack);
	if (!hkAttack)
		hkAttack = Virtual_Hook(_("BasePlayer"), _("OnAttacked"), &OnAtttackedHook); // HitInfo info
	if (!mvitem)
		mvitem = Virtual_Hook(_("ItemIcon"), _("TryToMove"), &hk_TryToMove);
	if (!DoFixedUpd)
		DoFixedUpd = Virtual_Hook(_("PlayerWalkMovement"), _("DoFixedUpdate"), &hk_DoFixedUpdate);
	if (!PlayerWM)
		PlayerWM = Virtual_Hook(_("PlayerWalkMovement"), _("ClientInput"), &hk_PlayerWalkMovement_ClientInput);
	
	
	// Virtual_Hook(_("BaseProjectile"), _("DoAttack"), &hk_DoAttack);
	/*if (!HKBlockJump)
		HKBlockJump = Virtual_Hook(_("PlayerWalkMovement"), _("BlockJump"), &hk_BlockJump);
	if (!BaseMovement_BlockJump)
		BaseMovement_BlockJump = Virtual_Hook(_("BasePlayer"), _("BlockJump"), &hk_BaseMovement_BlockJump);*/
	
	/*if (Target.Cur) {
		bool target_friend = false;
		bool target_enemy = false;
		int list_pos = 0;
		for (int i = 0; i < 100; i++) {
			BasePlayer* plya = (BasePlayer*)enemies[i];
			BasePlayer* plyb = (BasePlayer*)friends[i];
			if (plya = Target.Cur) {
				target_enemy = true;
				target_friend = false;
				list_pos = i;
				break;
			}
			else if (plyb = Target.Cur) {
				target_friend = true;
				target_enemy = false;
				list_pos = i;
				break;
			}
		}
		if (ToggleEnemy) {
			if (target_enemy) {
				enemies[list_pos] = NULL;
			}
			else enemies[list_pos] = (uintptr_t*)Target.Cur;
		}
		else if (ToggleFriend) {
			if (target_friend) {
				friends[list_pos] = NULL;
			}
			else friends[list_pos] = (uintptr_t*)Target.Cur;
		}
	}*/

	

	//if (ProjectileShootInited)
	{
		static bool psilent_hook = true;
		if (psilent_hook) {
			auto& serverrpc_playerprojectileattack = *(__int64*)(**(__int64**)(*(__int64*)(g_Base + offsets::Method$BaseEntity_ServerRPCPlayerProjectileShoot__) + 0x38) + 8);
			if (serverrpc_playerprojectileattack)
			{
				Hooks::PlayerProjectileShoot_orig = serverrpc_playerprojectileattack;
				serverrpc_playerprojectileattack = (DWORD64)&hook_PlayerProjectileShoot;
				psilent_hook = false;
			}
		}

		// if (ProjectileAttackInited)
		{
			static bool attack_hook = true;
			if (attack_hook) {
				auto& serverrpc_playerprojectileattack = *(__int64*)(**(__int64**)(*(__int64*)(g_Base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileAttack___) + 0x38) + 8);
				if (serverrpc_playerprojectileattack)
				{
					PlayerProjectileAttack_Orig = serverrpc_playerprojectileattack;
					serverrpc_playerprojectileattack = (DWORD64)&hook_PlayerProjectileAttack;
					attack_hook = false;
				}
			}
		}

		/*static bool prUpdate_hook = true;
		if (prUpdate_hook) {
			auto& serverrpc_playerprojectileupdate = *(__int64*)(**(__int64**)(*(__int64*)(g_Base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileRicochet___) + 0x38) + 8);
			Hooks::PlayerProjectileRicochet_orig = serverrpc_playerprojectileupdate;
			serverrpc_playerprojectileupdate = (DWORD64)&hook_PlayerProjectileRicochet;
			prUpdate_hook = false;
		}*/

		/*static bool prUpdate_hook = true;
		if (prUpdate_hook) {
			auto& serverrpc_playerprojectileupdate = *(__int64*)(**(__int64**)(*(__int64*)(g_Base + offsets::Method$BaseEntity_ServerRPC_PlayerProjectileUpdate___) + 0x38) + 8);
			Hooks::PlayerProjectileUpdate_orig = serverrpc_playerprojectileupdate;
			serverrpc_playerprojectileupdate = (DWORD64)&hook_PlayerProjectileUpdate;
			prUpdate_hook = false;
		}*/
	}
	float MEGAMAGICBULLETCALCULATION;
	static DWORD64 StoredMainCamera = 0;
	if (baseplayer) {

		if (LocalPlayer != baseplayer)
		{// Unity::LogoPng

			if (Unity::NicotineBundle)
				Unity::UnloadBundle(Unity::NicotineBundle, true);
			if (Unity::GGshader)
				Unity::UnloadBundle(Unity::GGshader, true);
			if (Unity::LogoPng)
				Unity::UnloadBundle(Unity::LogoPng, true);
			Unity::CanOverWriteAssets = true;

			GUI::InitAssets();

			if (!StoredMainCamera || Unity::CanOverWriteAssets)
				StoredMainCamera = Unity::get_main_camera();
			// assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_16.mat 
			// assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_14.mat
			// assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_06.mat // red 
			bool loaded1 = false, loaded2 = false, loaded3 = false, loaded4 = false, loaded5 = false;
			if (Unity::NicotineBundle && Unity::GGshader) {
				if (Unity::CanOverWriteAssets || GalaxyPink == 0) {
					//Galaxymaterial = Unity::LoadAsset(Unity::GGshader, _(L"assets/hologramshader.shader"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Shader"))); loaded1 = true;
					GalaxyPink = Unity::LoadAsset(Unity::GGshader, _(L"assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_16.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded1 = true;
				}
				if (Unity::CanOverWriteAssets || StormShader == 0) {
					StormShader = Unity::LoadAsset(Unity::NicotineBundle, _(L"assets/magicrainbowdiscogridshader/tazoshader/magicrainbowdiscogridshader/material/mat_dance_rainbow.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded2 = true;
				}
				if (Unity::CanOverWriteAssets || GalaxyGreen == 0) {
					// StandardMat = Unity::LoadAsset(Unity::GGshader, _(L"assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_14.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded3 = true;
					GalaxyGreen = Unity::LoadAsset(Unity::GGshader, _(L"assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_14.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded3 = true;
				}
				if (Unity::CanOverWriteAssets || GalaxyRed == 0) {
					//	FlatShader = Unity::LoadAsset(Unity::GGshader, _(L"assets/chams.shader"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Shader"))); loaded4 = true;
					GalaxyRed = Unity::LoadAsset(Unity::GGshader, _(L"assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_07.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded4 = true;
				}
				if (Unity::CanOverWriteAssets || GalaxyBlue == 0) {
					//	FlatShader = Unity::LoadAsset(Unity::GGshader, _(L"assets/chams.shader"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Shader"))); loaded4 = true;
					GalaxyBlue = Unity::LoadAsset(Unity::GGshader, _(L"assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_08.mat"), Il2cpp::TypeGetObject(_("UnityEngine"), _("Material"))); loaded5 = true;
				} // assets/sinevfx/galaxymaterials/resources/materials/galaxymaterial_07.mat
			}
			if (loaded1 && loaded2 && loaded3 && loaded4 && loaded5)
				Unity::CanOverWriteAssets = false;

			Unity::FindMatrix(StoredMainCamera);
			LocalPlayer = baseplayer;
		}

		GetHeldEntity(baseplayer);

		// baseplayer->SetFlag(131072);

		float MaxDesync = Vars::Exploits::DesyncDist * 0.001;
		
		MyRGB = Color(RGBA().r, RGBA().g, RGBA().b, 255);

		Vector3 MyEyePos = baseplayer->GetNetworkEyePosition();// baseplayer->GetEyes()->EyePosition();
		MyEyePos += ManipulationAngle;
		EyePos = MyEyePos;

		// Target = baseplayer->FindBestTarget(EyePos);
		if (Target.Cur)
			Vars::Exploits::BulletTpExternded = Vars::Exploits::isBulletTpExternded && Classes::get_mounted((DWORD64)Target.Cur) ? true : false;
		lowvelocity::find_prediction_angle();
		uintptr_t* mount_ptr = (DWORD64*)Classes::get_mounted((DWORD64)baseplayer);
		float num5 = mount_ptr ? 25 : 5.5;

		double desyncTime = (Unity::RealtimeSinceStartup() - baseplayer->lastSentTickTime());
		Vars::Exploits::DesyncTime = desyncTime;
		float num = 1.f + AntiHack::eye_forgiveness;
		float eye_clientframes = AntiHack::eye_clientframes;
		float eye_serverframes = AntiHack::eye_serverframes;
		float num2 = eye_clientframes / 60.f;
		float num3 = eye_serverframes * max(Unity::get_deltaTime(), Unity::get_smoothDeltaTime(), Unity::get_fixedDeltaTime());
		float num4 = (Vars::Exploits::DesyncTime + num2 + num3) * num;
		float num6 = 5.5 + LocalPlayer->GetParentVelocity().Magnitude() + LocalPlayer->GetMountVelocity().Magnitude();
		float num7 = LocalPlayer->BoundsPadding() + num4 * num6 + 0.125f;

		double EyeDist = num7/*num7*/;/*(0.1f + ((desyncTime + 2.f / 60.f) * 1.5f) * 5.5) + 0.125f;*///  (0.1f + ((desyncTime + 2.f / 60.f) * 1.50f) * num5) - 0.59375;
		if (Vars::Exploits::Manipulation && Manipulating)
			LastDesyncDist = max(LastDesyncDist, EyeDist);
		if (Vars::Misc::BrightNight || Vars::Misc::TimeChanger || Vars::Misc::SkyColor || Vars::Misc::AmbientColor)
			Ambient();

		CustumTime();

		if (Vars::Misc::NoFallDamage) baseplayer->NoFall();

		if (GUI::open)
		{
			if (Vars::Misc::RayLenthChanger) {
				Classes::set_atmosphere_rayleigh(Vars::Misc::RayleighValue);
			}
			else
			{
				Classes::set_atmosphere_rayleigh(-1);
			}
		}

		if (Vars::Misc::MassSuicide)
			Hooks::OnLand(baseplayer, -1337);

		if (Vars::Misc::DoorKnocker) {
			AimResult closest = AimResult::get_closest_object(baseplayer->GetTransform(47)->Position(), _(""), Vector3::Zero(), Vector3::Zero(), Vector3::Zero(), true, _("Door"));
			if (closest.valid && Maths::Calc3D_Dist(baseplayer->GetBoneByID(head), closest.pos) < 3) {
				EbynMozga((DWORD64)closest.entity);
			}
		}

		if (Vars::Misc::ShootMounted) {
			auto mountable = baseplayer->Mountable();
			if (mountable)
				mountable->CanwieldItem(true);
		}

		/*DWORD64 CapsuleCollider = Read<DWORD64>((DWORD64)baseplayer + O::BasePlayer::playerCollider);
		if (CapsuleCollider)
			reinterpret_cast<void(*)(DWORD64, float)>((DWORD64)(g_Base + 0x25F43E0))(CapsuleCollider, 0.1);*/

		// PredictPoint

		/*if (LocalPlayer->GetActiveWeapon() != 0)
		{

		}
		else
		{
			PredictPoint = Vector3::Zero();
		}*/
		//RaycastHit outRay;
		//auto mask = 10551296 | 1503731969 | 131072 | 1218519297 | 65536 | 1218519041;
		//auto BigRayCast = reinterpret_cast<bool(*)(Vector3, Vector3, RaycastHit*, float, int, QueryTriggerInteraction)>(g_Base + offsets::o_RaycastBig);
		//if (BigRayCast(LocalPlayer->GetBoneByID(head), LocalPlayer->GetEyes()->BodyForward(), &outRay, 400, mask, QueryTriggerInteraction::Ignore))
		//{
		//	// outRay.point is out position that u need
		//}
		//if (Target.Cur)
		//{
		//	reinterpret_cast<bool(*)(BasePlayer*)>(g_Base + 0x3589E0)(Target.Cur);

		//	if (reinterpret_cast<bool(*)(BasePlayer*)>(g_Base + 0xAF83B0)) // private bool IsEnemy() { }
		//	{
		//		Classes::DDrawSphere(Target.Pos, 0.5, { 1,1,1,1 }, 0.02, false);
		//	}
		//}
		//while (true)
		//{
		//	
		//	if (Target.Cur)dx
		//	{
		//		Read<bool>(g_Base + 0xAF83B0, );

		//	}
		//	// 0x3589E0 
		//}

		//simulateMotion(EyePos, LocalPlayer->GetActiveWeapon()->HeldEntity()->WeaponData().initial_velocity, LocalPlayer->GetActiveWeapon()->HeldEntity()->WeaponData().initial_velocity);

		baseplayer->DebugColliders();

		if (Vars::Misc::SpiderMan)
			baseplayer->SpiderMan();

		if (Vars::Misc::BlockCommands) {
			BlockServerComands();
		}
		
		if (Vars::Misc::AdminFlag) {
			baseplayer->SetFlag(4);
		}

		if (Vars::Misc::InfinityJump)
			baseplayer->InfinityJump();

		//if (Vars::Misc::PlayerFovBool || Vars::Misc::PlayerZoomBool && Zooming)
			baseplayer->SetFov();

		static float DefaultAspect = 0;
		if (!DefaultAspect)
			DefaultAspect = Maths::m_Abs( Unity::get_aspect(StoredMainCamera) );
		// Vars::Misc::Aspect
		if (Vars::Misc::AspectRatio)
		{
			Unity::SetAspect(StoredMainCamera, Vars::Misc::Aspect);
		}
		else if (DefaultAspect && !Vars::Misc::AspectRatio)
		{
			Unity::SetAspect(StoredMainCamera, DefaultAspect);
		}
		/*if (RaidInfo.Pos != Vector3(0,0,0))
			Classes::DDrawText((DWORD64)Il2cpp::new_string(_("Raid")), RaidInfo.Pos, { 255,255 ,255,255 }, 20, 1);*/


			//GUI::set_color(Color(0, 1, 0, 1));
			//Classes::DDrawText((DWORD64)Il2cpp::new_string(_("Zalupa")), Vector3(20, 20,0), { 255,255 ,255,255 }, 10);

			/*if (Vars::Aim::AimBot && Unity::GetKeyInt(Vars::Keys::AimKey) && Target.Cur)
				DoAimBot(Target.Cur);*/

		if (Vars::Visuals::PlayerEsp::MovmentLine)
		{
			Color Col = RGBA();
			Classes::DDrawLine(baseplayer->GetPlayerModel()->ModelPosition(), baseplayer->lastSentTick()->position(), { ColorPicker::MovmentRGBBool ? Color(Col.r,Col.g,Col.b,255) : ColorPicker::MovmentLine }, 2.f, false, true);
		}
		//public void ServerRPC<T1, T2>(SendMethod sendMethod, string funcName, T1 arg1, T2 arg2)

		if (Vars::Exploits::Manipulation && Manipulating) // || Vars::Aim::InstaKill
		{
			baseplayer->ClientTickInterval(MaxDesync);
		}
		else {
			float MinDesync = Vars::Exploits::MinDecync * 0.001;
			baseplayer->ClientTickInterval(MinDesync); }
		if (Vars::Exploits::Manipulation && Manipulating)
		{
			if (Target.Cur) Manipulation::DoManipulation(baseplayer, Target.Pos, EyeDist);

			if (Vars::Exploits::Visualize) {

				static float desyncPoint = 0;
				float x, z = 0;
				if (desyncPoint < 360)
				{
					desyncPoint += 0.08;
				}
				else
				{
					desyncPoint = 0;
				}
				Vector3 playerPos = LocalPlayer->GetBoneByID(head);

				x = Maths::m_Sin(desyncPoint) * EyeDist;
				z = Maths::m_Cos(desyncPoint) * EyeDist;

				Classes::DDrawSphere(playerPos + Vector3(-x, 0, -z), 0.06, Color(0.95, 0.95, 0.95, 0.95), 0.06, false);
				Classes::DDrawSphere(playerPos + Vector3(x, 0, z), 0.06, Color(0.95, 0.95, 0.95, 0.95), 0.06, false);
			}
		}
		else if (!ManipulationAngle.Empty())
		{
			ManipulationAngle = Vector3::Zero();
		}

		bool chamsdist = false;
		if (!chamsdist || baseplayer->IsSleeping())
		{
			auto klazz = Il2cpp::InitClass(_("Culling"), _("ConVar"));
			UINT64 st = safe_read(klazz + 0xB8, UINT64);
			safe_write(st + 0x4, 400.f, float);
			safe_write(st + 0x8, 0, float);
			chamsdist = true;
		}

		WeaponFix();
		HandChams();
	}

	if (Vars::Visuals::PlayerEsp::HandChams || Vars::Visuals::PlayerEsp::WeaponChams) { // WeaponChams
		auto pizdec = Il2cpp::InitClass(_("Graphics"), _("ConVar"));
		auto static_fields = safe_read(pizdec + 0xb8, uintptr_t);
		safe_write(static_fields + 0x7D, false, bool);
	}

	if (Vars::Misc::InstaRevive && Unity::GetKeyInt(Vars::Keys::InstaRevive))
	{
		if (FindCurTarget.Cur && FindCurTarget.Wounded && !FindCurTarget.Heli && Maths::Calc3D_Dist(LocalPlayer->GetBoneByID(head), FindCurTarget.Pos) < 3)
			Classes::ServerRPC((DWORD64)Target.Cur, _(L"RPC_Assist"));
	}

	//public class ViewmodelAspectOffset : MonoBehaviour // TypeDefIndex: 3408
	//{
	//	// Fields
	//	public Vector3 OffsetAmount; // 0x18
	//	[Tooltip("What aspect ratio should we start moving the viewmodel? 16:9 = 1.7, 21:9 = 2.3")]
	//	public float aspectCutoff; // 0x24

	if (Vars::Misc::SilentStash && SilentStashing)
	{
		AimResult Closest = AimResult::get_closest_object(baseplayer->GetTransform(47)->Position(), _("small_stash_deployed.prefab"));
		if (Closest.valid)
		{
			if (Closest.dist < 3) Classes::ServerRPC((DWORD64)Closest.entity, _(L"RPC_OpenLoot"));
		}
	}
	if (Vars::Misc::SilentTurret)
	{
		if (ClosestTurret.Entity != 0)
		{
			if (ClosestTurret.Dist < 3) Classes::ServerRPC((DWORD64)ClosestTurret.Entity, _(L"AddSelfAuthorize"));
		}
	}
	float last_recycler = 0.f;
	if (Vars::Misc::StopRecycler && Unity::get_fixedTime() > last_recycler + 0.35f)
	{
		if (ClosestRecycler.Entity != 0)
		{
			if (ClosestRecycler.Dist < 3)
			{
				Classes::ServerRPC((DWORD64)ClosestRecycler.Entity, _(L"SVSwitch"));
				last_recycler = Unity::get_fixedTime();
			}
		}
	}

	/*auto NewTickInterpolator = Il2cpp::InitClass(_("TickInterpolator"), _(""));
	auto static_fields = safe_read(NewTickInterpolator + 0xb8, uintptr_t);*/
	// Player_Server

	//if (HeldEntity)
	//{ // HeldEntity
	//	Vector3 vector = LocalPlayer->GetEyes()->EyePosition();
	//	Vector3 vector2 = LocalPlayer->GetEyes()->BodyForward();
	//	float num = Classes::GetAimCone(HeldEntity);
	//	if (num > 0.f) {
	//		vector2 = Classes::GetModifiedAimCone(num, vector2, true);
	//	}
	//	
	//	Vector3 rocket_vel = Classes::GetInheritedVelocity(HeldEntity, LocalPlayer, vector2) + vector2 * AngleY/*component2.speed*/;

	//	/*float num2 = 1.f;
	//	RaycastHit raycastHit;

	//	auto BigRayCast = reinterpret_cast<bool(*)(Vector3, Vector3, RaycastHit*, float, int, QueryTriggerInteraction)>(g_Base + offsets::o_RaycastBig);
	//	if (BigRayCast(vector, vector2, &raycastHit, num2, 1237003025, QueryTriggerInteraction::Ignore))
	//	{
	//		num2 = raycastHit.distance - 0.1f;
	//	}*/

	//	RaycastHit outRay;
	//	auto mask = 10551296 | 1503731969 | 131072 | 1218519297 | 65536 | 1218519041;
	//	auto BigRayCast = reinterpret_cast<bool(*)(Vector3, Vector3, RaycastHit*, float, int, QueryTriggerInteraction)>(g_Base + offsets::o_RaycastBig);
	//	//if (BigRayCast(vector, aimDirection, &outRay, 400, mask, QueryTriggerInteraction::Ignore))
	//	//{
	//	//	Classes::DDrawSphere(outRay.point, 0.2, { 1,1,1,1 }, 0.01, false);
	//	//	// outRay.point is out position that u need
	//	//}

	//	Vector3 endPredict = simulateMotion(vector, rocket_vel, 0.25, 0, 0.03125, 8);
	//	Vector3 aimDirection = Classes::GetModifiedAimCone(0, endPredict - vector, true);

	//	if (BigRayCast(vector, aimDirection, &outRay, 400, mask, QueryTriggerInteraction::Ignore))
	//	{
	//		Classes::DDrawSphere(outRay.point, 0.2, { 1,1,1,1 }, 0.01, false);
	//		// outRay.point is out position that u need
	//	}
	//}

	Unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Water, !Vars::Misc::Jesus);
	Unity::IgnoreLayerCollision(layer::PlayerMovement, layer::Tree, Vars::Misc::RemoveCollision);
	Unity::IgnoreLayerCollision(layer::PlayerMovement, layer::AI, Vars::Misc::RemoveCollision);

	if (Target.Cur)
		SimulateMovement();

	//if (Vars::Exploits::BulletTpType == 0)
	//	Vars::Exploits::BulletTpDist = 1.6;
	//if (Vars::Exploits::BulletTpType == 1)
	//	Vars::Exploits::BulletTpDist = 1.8;
	//if (Vars::Exploits::BulletTpType == 2)
	//	Vars::Exploits::BulletTpDist = 1.95;
	//if (Vars::Exploits::BulletTpType == 3) {
	//	float endScanRange = 2.95;
	//	Vars::Exploits::BulletTpDist = endScanRange;
	//}
		

	if (Target.Cur && Vars::Exploits::BulletTp && Vars::Exploits::DrawBulletTp && !Target.Heli && !Target.Turret)
	{
		float ScanRange = Vars::Exploits::BulletTpExternded ? 6 : Vars::Exploits::BulletTpDist;
		Classes::DDrawSphere(Target.Cur->ManipPoint(), Vars::Exploits::BulletTpDist, { 1,1,1,1 }, 0.01, false);
	}


	Hooks::ClientInput_Orig(baseplayer, state);

	if (Vars::Misc::JitterAA) {
		Vector3 spin_angles = Vector3::Zero();
		Vector3 real_angles = state->AimAngles();

		spin_angles = Vector3(Maths::my_rand() % 999 + -200, Maths::my_rand() % 600 + -200, Maths::my_rand() % 200 + -200);//Vector3(-999, Maths::my_rand() % 999, Maths::my_rand() % 999);

		/*spin_angles.x = -999.f;
		spin_angles.z = 0.f;
		spin_angles.y = real_angles.y - 180.f;*/

		state->AimAngles(spin_angles);
	}

	//static bool didCall = false;
	//if (!didCall) { // 0x182746C30
	//	QwordSwap(hk_get_transform, g_Base + 0x338FDE0, get_trans_orig); // first qword in InitializeVelocity
	//	QwordSwap(hk_getFixedTime, g_Base + 0x3390270, get_fixedTime_orig); // qword in get_transform // 0x182757310
	//	QwordSwap(hk_Run, g_Base + 0x32155E0, get_run_orig); // qword in get_transform // 0x182757310
	//	didCall = true;
	//} // 0x2746C30 
}

