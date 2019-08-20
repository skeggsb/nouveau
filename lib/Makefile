LIBNVIF_CC := $(CFLAGS) -I$(drm) -fPIC -Wframe-larger-than=1024
LIBNVIF_LD := $(LDFLAGS) -shared -lpciaccess -lpthread -ldrm

src  := $(drm)
include $(src)/nvif/Kbuild
include $(src)/nvkm/Kbuild

fucs := $(drm)/nvkm/engine/ce/fuc/gt215.fuc3.h \
	$(drm)/nvkm/engine/ce/fuc/gf100.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/hubgf100.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/hubgf117.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/hubgk104.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/hubgk110.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/hubgk208.fuc5.h \
	$(drm)/nvkm/engine/gr/fuc/hubgm107.fuc5.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgf100.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgf117.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgk104.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgk110.fuc3.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgk208.fuc5.h \
	$(drm)/nvkm/engine/gr/fuc/gpcgm107.fuc5.h \
	$(drm)/nvkm/subdev/pmu/fuc/gt215.fuc3.h \
	$(drm)/nvkm/subdev/pmu/fuc/gf100.fuc3.h \
	$(drm)/nvkm/subdev/pmu/fuc/gf119.fuc4.h \
	$(drm)/nvkm/subdev/pmu/fuc/gk208.fuc5.h \
	$(drm)/nvkm/engine/sec/fuc/g98.fuc0s.h
drms := $(addprefix $(lib)/, $(nvif-y)) \
	$(addprefix $(lib)/, $(nvkm-y))
srcs := $(lib)/bit.o \
	$(lib)/drm.o \
	$(lib)/firmware.o \
	$(lib)/intr.o \
	$(lib)/main.o \
	$(lib)/null.o \
	$(lib)/platform.o \
	$(lib)/rb.o \
	$(lib)/tegra.o \
	$(lib)/work.o
outp := $(lib)/libnvif.so

deps-fuc := $(fucs:$(drm)/%.h=$(lib)/%.d)
deps-drm := $(drms:%.o=%.d)
deps-src := $(srcs:%.o=%.d)

$(deps-fuc): $(lib)/%.d : $(drm)/%
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $<.h -MF $@ -xc $<
$(deps-drm): $(lib)/%.d : $(drm)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $(patsubst %.d,%.o,$@) -MF $@ $<
$(deps-src): $(lib)/%.d : $(lib)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(LIBNVIF_CC) -E -MM -MP -MT $(patsubst %.d,%.o,$@) -MF $@ $<

$(filter %.fuc0s.h,$(fucs)): %.fuc0s.h : %.fuc0s
	@echo "  FUC0S    "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc0 -Fcrypt -o $@
	@sed -i -e 's:^uint32_t:static uint32_t:g' \
		-e '1s:^:/* SPDX-License-Identifier\: MIT */\n:' $@
$(filter %.fuc3.h,$(fucs)): %.fuc3.h : %.fuc3
	@echo "  FUC3     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc3 -o $@
	@sed -i -e 's:^uint32_t:static uint32_t:g' \
		-e '1s:^:/* SPDX-License-Identifier\: MIT */\n:' $@
$(filter %.fuc4.h,$(fucs)): %.fuc4.h : %.fuc4
	@echo "  FUC4     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc4 -o $@
	@sed -i -e 's:^uint32_t:static uint32_t:g' \
		-e '1s:^:/* SPDX-License-Identifier\: MIT */\n:' $@
$(filter %.fuc5.h,$(fucs)): %.fuc5.h : %.fuc5
	@echo "  FUC5     "$@
	@$(call ENVYPP,$<) | $(ENVYAS) -a -w -mfuc -Vfuc5 -o $@
	@sed -i -e 's:^uint32_t:static uint32_t:g' \
		-e '1s:^:/* SPDX-License-Identifier\: MIT */\n:' $@

$(drms): $(lib)/%.o : $(drm)/%.c
	@echo "  CC       "$@
	@$(CC) $(LIBNVIF_CC) -o $@ -c $<
$(srcs): $(lib)/%.o : $(lib)/%.c
	@echo "  CC       "$@
	@$(CC) $(LIBNVIF_CC) -o $@ -c $<
$(outp): $(drms) $(srcs)
	@echo "  CCLD     "$@
	@$(CC) $(LIBNVIF_LD) -o $@ $^

deps += $(deps-fuc) $(deps-drm) $(deps-src)
objs += $(drms) $(srcs)
libs += $(outp)
fws  += $(fucs)
