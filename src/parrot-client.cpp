#include <ulog.h>
#include <pdraw-vsink/pdraw_vsink.h>


int main(int argc, char **argv){
    int status = EXIT_SUCCESS, res, i;
	struct pdraw_vsink *vsink = NULL;
	struct pdraw_media_info *media_info = NULL;

	if (argc < 2) {
		ULOGE("usage: %s <url>", argv[0]);
		exit(EXIT_FAILURE);
	}

	res = pdraw_vsink_start(argv[1], &media_info, &vsink);
	if (res < 0 || media_info == NULL) {
		ULOG_ERRNO("pdraw_vsink_start", -res);
		exit(EXIT_FAILURE);
	}
	ULOGI("started");

	ULOGI("media_info: name=%s, path=%s",
	      media_info->name,
	      media_info->path);
	ULOGI("media_info: duration=%.3fs, res=%ux%u, framerate=%u/%u",
	      media_info->duration / 1000000.0,
	      media_info->video.raw.info.resolution.width,
	      media_info->video.raw.info.resolution.height,
	      media_info->video.raw.info.framerate.num,
	      media_info->video.raw.info.framerate.den);


    res = pdraw_vsink_stop(vsink);
	if (res < 0)
		ULOG_ERRNO("pdraw_vsink_stop", -res);
	/* media_info won't be valid after pdraw_vsink_stop() */

	ULOGI("%s", (status == EXIT_SUCCESS) ? "success!" : "failed!");
	exit(status);

    return 0;
}
