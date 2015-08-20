#ifndef __NVKM_DMA_USER_H__
#define __NVKM_DMA_USER_H__
#include "priv.h"

#define nvkm_dmaobj_create(p,e,c,pa,sa,d)                                      \
	nvkm_dmaobj_create_((p), (e), (c), (pa), (sa), sizeof(**d), (void **)d)

int nvkm_dmaobj_create_(struct nvkm_object *, struct nvkm_object *,
			struct nvkm_oclass *, void **, u32 *,
			int, void **);
#define _nvkm_dmaobj_dtor nvkm_object_destroy
#define _nvkm_dmaobj_init _nvkm_object_init
#define _nvkm_dmaobj_fini _nvkm_object_fini

extern struct nvkm_oclass nv04_dmaeng_sclass[];
extern struct nvkm_oclass nv50_dmaeng_sclass[];
extern struct nvkm_oclass gf100_dmaeng_sclass[];
extern struct nvkm_oclass gf110_dmaeng_sclass[];

int nv04_dmaobj_bind(struct nvkm_dmaobj *, struct nvkm_gpuobj *,
		     struct nvkm_gpuobj **);
int nv50_dmaobj_bind(struct nvkm_dmaobj *, struct nvkm_gpuobj *,
		     struct nvkm_gpuobj **);
int gf100_dmaobj_bind(struct nvkm_dmaobj *, struct nvkm_gpuobj *,
		      struct nvkm_gpuobj **);
int gf110_dmaobj_bind(struct nvkm_dmaobj *, struct nvkm_gpuobj *,
		      struct nvkm_gpuobj **);

#endif
