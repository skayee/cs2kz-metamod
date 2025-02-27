#pragma once
#include "../kz.h"
#include "iserver.h"
#include "networksystem/inetworkserializer.h"

namespace KZ::quiet
{
	void OnCheckTransmit(CCheckTransmitInfo **pInfo, int infoCount);

	void OnPostEvent(INetworkSerializable *pEvent, const void *pData, const uint64 *clients);
} // namespace KZ::quiet

class KZQuietService : public KZBaseService
{
	using KZBaseService::KZBaseService;
	u8 lastObserverMode;
	CHandle<CBaseEntity> lastObserverTarget;
	bool hideWeapon {};

public:
	bool hideOtherPlayers {};
	virtual void Reset() override;

	void ToggleHide();
	void UpdateHideState();
	void SendFullUpdate();
	bool ShouldHide();
	bool ShouldHideIndex(u32 targetIndex);

	bool ShouldHideWeapon()
	{
		return this->hideWeapon;
	}

	void ToggleHideWeapon()
	{
		this->hideWeapon = !this->hideWeapon;
	}
};
