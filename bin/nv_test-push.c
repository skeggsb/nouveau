/*
 * Copyright 2020 Red Hat Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */
#define __must_check
#include <nvif/pushc37b.h>
#include "util.h"

#if 1
#define NV1234_TEST_MTHD0 0x0100
#define NV1234_TEST_MTHD1 0x0104
#define NV1234_TEST_MTHD2 0x0108
#define NV1234_TEST_MTHD3 0x010c
#define NV1234_TEST_MTHD4 0x0110
#define NV1234_TEST_MTHD5 0x0114
#define NV1234_TEST_MTHD6 0x0118
#define NV1234_TEST_MTHD7 0x011c
#define NV1234_TEST_MTHD8 0x0120
#define NV1234_TEST_MTHD9 0x0124
#else
#define TEST_MTHD0 0x0100
#define TEST_MTHD1 0x0104
#define TEST_MTHD2 0x0108
#define TEST_MTHD3 0x010c
#define TEST_MTHD4 0x0110
#define TEST_MTHD5 0x0114
#define TEST_MTHD6 0x0118
#define TEST_MTHD7 0x011c
#define TEST_MTHD8 0x0120
#define TEST_MTHD9 0x0124

#undef PUSH_IMMD
#undef PUSH_MTHD
#undef PUSH_1INC
#undef PUSH_NINC
#define PUSH_IMMD PUSH_NVNI
#define PUSH_MTHD PUSH_NVSQ
#define PUSH_1INC PUSH_NV1I
#define PUSH_NINC PUSH_NVNI
#endif

int
main(int argc, char **argv)
{
	u32 pushbuf[1024], data[] = { 0xfffffff0, 0xfffffff1, 0xfffffff2 };
	struct nvif_parent parent = {
		.func = &(const struct nvif_parent_func) {
			.debugf = u_printf,
			.errorf = u_printf,
		},
	};
	struct nvif_client client = {
		.object.parent = &parent,
		.object.name = "test-push",
	};
	struct nvif_push _push = {
		.mem.object.parent = client.object.parent,
		.mem.object.client = &client,
		.mem.object.name = "pushbuf",
		.mem.object.map.ptr = pushbuf,
		.bgn = pushbuf,
		.cur = pushbuf,
		.end = pushbuf + 0x1000,
	}, *push = &_push;
	FILE *f = fopen(argv[1], "r");

	// incrementing
	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555,
				TEST_MTHD5, 0x66666666);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555,
				TEST_MTHD5, 0x66666666,
				TEST_MTHD6, 0x77777777);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555,
				TEST_MTHD5, 0x66666666,
				TEST_MTHD6, 0x77777777,
				TEST_MTHD7, 0x88888888);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555,
				TEST_MTHD5, 0x66666666,
				TEST_MTHD6, 0x77777777,
				TEST_MTHD7, 0x88888888,
				TEST_MTHD8, 0x99999999);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, 0x33333333,
				TEST_MTHD3, 0x44444444,
				TEST_MTHD4, 0x55555555,
				TEST_MTHD5, 0x66666666,
				TEST_MTHD6, 0x77777777,
				TEST_MTHD7, 0x88888888,
				TEST_MTHD8, 0x99999999,
				TEST_MTHD9, 0xaaaaaaaa);

	PUSH_MTHD(push, NV1234, TEST_MTHD0, data, ARRAY_SIZE(data));

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, data, ARRAY_SIZE(data));

	PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x11111111,
				TEST_MTHD1, 0x22222222,
				TEST_MTHD2, data, ARRAY_SIZE(data));

	for (int i = 0; i < 10; i++)
		PUSH_MTHD(push, NV1234, TEST_MTHD0, 0x55aa55aa);

	for (u32 *data = push->bgn; data < push->cur; data++) {
		if (f) {
			u32 expected;
			if (fscanf(f, "%08x\n", &expected) != 1 || data[0] != expected) {
				fprintf(stderr, "failed\n");
				f = NULL;
			}
		}
		printf("%08x\n", *data);
	}

	if (f) {
		fprintf(stderr, "ok!\n");
		return 0;
	}

	return 1;
}