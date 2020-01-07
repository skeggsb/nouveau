/*
 * Copyright 2016 Red Hat Inc.
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
 *
 * Authors: Ben Skeggs
 */
#include <nvif/os.h>

static int
request_firmware_(const struct firmware **pfw, const char *prefix,
		  const char *name, struct device *dev)
{
	struct firmware *fw = *(void **)pfw = malloc(sizeof(*fw));
	char *path;
	int fd;

	if (!(path = malloc(strlen(prefix) + strlen(name) + 1)))
		return -ENOMEM;
	sprintf(path, "%s%s", prefix, name);

	fd = open(path, O_RDONLY);
	free(path);
	if (fd >= 0) {
		off_t len = lseek(fd, 0, SEEK_END);
		fw->data = malloc(len);
		fw->size = pread(fd, (void *)fw->data, len, 0);
		return 0;
	}

	free(fw);
	return -EINVAL;
}

int
request_firmware(const struct firmware **pfw, const char *name,
		 struct device *dev)
{
	if (!request_firmware_(pfw, "/lib/firmware/", name, dev))
		return 0;
	if (!request_firmware_(pfw, "", name, dev))
		return 0;
	return -EINVAL;
}

void
release_firmware(const struct firmware *fw)
{
	if (fw) {
		free((void *)fw->data);
		free((void *)fw);
	}
}
