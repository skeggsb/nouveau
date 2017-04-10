/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __NVKM_FB_RAM_PRIV_H__
#define __NVKM_FB_RAM_PRIV_H__
#include "priv.h"
#include <subdev/bios/M0209.h>

int  nvkm_ram_ctor(const struct nvkm_ram_func *, struct nvkm_fb *,
		   enum nvkm_ram_type, u64 size, struct nvkm_ram *);
int  nvkm_ram_new_(const struct nvkm_ram_func *, struct nvkm_fb *,
		   enum nvkm_ram_type, u64 size, struct nvkm_ram **);
void nvkm_ram_del(struct nvkm_ram **);
int  nvkm_ram_init(struct nvkm_ram *);

extern const struct nvkm_ram_func nv04_ram_func;

int  nv50_ram_ctor(const struct nvkm_ram_func *, struct nvkm_fb *,
		   struct nvkm_ram *);

int gf100_ram_new_(const struct nvkm_ram_func *, struct nvkm_fb *,
		   struct nvkm_ram **);
int  gf100_ram_ctor(const struct nvkm_ram_func *, struct nvkm_fb *,
		    struct nvkm_ram *);
int gf100_ram_probe_fbps(struct nvkm_device *, unsigned long *);
int gf100_ram_probe_fbp_ltcs(struct nvkm_device *, int);
u32  gf100_ram_probe_fbpa_amount(struct nvkm_device *, int);
int gf100_ram_init(struct nvkm_ram *);
int gf100_ram_calc(struct nvkm_ram *, u8, u32);
int gf100_ram_prog(struct nvkm_ram *);
void gf100_ram_tidy(struct nvkm_ram *);

int gf108_ram_probe_fbpas(struct nvkm_device *, unsigned long *);

int gk104_ram_new_(const struct nvkm_ram_func *, struct nvkm_fb *,
		   struct nvkm_ram **);
void *gk104_ram_dtor(struct nvkm_ram *);
int gk104_ram_init(struct nvkm_ram *);
int gk104_ram_calc(struct nvkm_ram *, u8, u32);
int gk104_ram_prog(struct nvkm_ram *);
void gk104_ram_tidy(struct nvkm_ram *);

int gm107_ram_probe_fbpas(struct nvkm_device *, unsigned long *);

int gm200_ram_probe_fbps(struct nvkm_device *, unsigned long *);
int gm200_ram_probe_fbp_ltcs(struct nvkm_device *, int);

/* DDR link training */
struct gt215_ram_train {
	u16 mask;
	struct nvbios_M0209S remap;
	struct nvbios_M0209S type00;
	struct nvbios_M0209S type01;
	struct nvbios_M0209S type04;
	struct nvbios_M0209S type06;
	struct nvbios_M0209S type07;
	struct nvbios_M0209S type08;
	struct nvbios_M0209S type09;
};
int gt215_ram_train_type(struct nvkm_ram *ram, int i, u8 ramcfg,
		     struct gt215_ram_train *train);
int gf100_ram_train_init(struct nvkm_ram *ram);

/* RAM type-specific MR calculation routines */
int nvkm_sddr2_calc(struct nvkm_ram *);
int nvkm_sddr3_calc(struct nvkm_ram *);
int nvkm_gddr3_calc(struct nvkm_ram *);
int nvkm_gddr5_calc(struct nvkm_ram *, bool nuts);

int nv04_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv10_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv1a_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv20_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv40_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv41_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv44_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv49_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv4e_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int nv50_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gt215_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int mcp77_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gf100_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gf108_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gk104_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gm107_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gm200_ram_new(struct nvkm_fb *, struct nvkm_ram **);
int gp100_ram_new(struct nvkm_fb *, struct nvkm_ram **);
#endif
