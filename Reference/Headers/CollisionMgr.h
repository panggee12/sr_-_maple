#pragma once
#include "Base.h"

BEGIN(Engine)
class CCollisionMgr final : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)
public:
	CCollisionMgr();
	virtual ~CCollisionMgr() = default;

public:
	bool CollisionCheck(class CTransform* p1Trans, class CTransform* p2Trans, _float fTimeDelta, _float3 f1Scale, _float3 f2Scale);
	bool Collision_Rect_Cube(CTransform* p1Trans, _float3 v1Pos, _float3 v2Pos, _float fTimeDelta, _float3 fScale);
	bool CollisionBlock(class CTransform* p1Trans, class CTransform* p2Trans, _float fTimeDelta);

public:
	virtual void Free()override;
};
END
