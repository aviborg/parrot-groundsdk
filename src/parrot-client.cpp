#include <ulog.h>
#include <pdraw-vsink/pdraw_vsink.h>

int main(int argc, char **argv)
{
	int status = EXIT_SUCCESS, res, i;
	struct pdraw_vsink *vsink = NULL;
	struct pdraw_media_info *media_info = NULL;

	if (argc < 2)
	{
		ULOGE("usage: %s <url>", argv[0]);
		exit(EXIT_FAILURE);
	}

	res = pdraw_vsink_start(argv[1], &media_info, &vsink);
	if (res < 0 || media_info == NULL)
	{
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
	for (i = 0; i < 300; i++)
	{
		struct pdraw_video_frame frame_info = {VDEF_FRAME_TYPE_UNKNOWN};
		struct mbuf_raw_video_frame *frame = NULL;
		struct vmeta_frame *frame_meta = NULL;
		unsigned int plane_count;

		/* Get a new frame */
		res = pdraw_vsink_get_frame(vsink, NULL, &frame_info, &frame);
		if (res < 0)
		{
			ULOG_ERRNO("pdraw_vsink_get_frame", -res);
			continue;
		}

		/* Get frame information */
		ULOGI("frame #%d (width=%d height=%d)",
			  i + 1,
			  frame_info.raw.info.resolution.width,
			  frame_info.raw.info.resolution.height);

		/* Get the video metadata */
		res = mbuf_raw_video_frame_get_metadata(frame, &frame_meta);
		if (res < 0 && res != -ENOENT)
			ULOG_ERRNO("mbuf_raw_video_frame_get_metadata", -res);
		if (frame_meta != NULL)
		{
			uint8_t battery_percentage;
			vmeta_frame_get_battery_percentage(frame_meta,
											   &battery_percentage);
			ULOGI("metadata: battery_percentage=%d%%",
				  battery_percentage);
		}

		/* Get the frame planes */
		plane_count =
			vdef_get_raw_frame_plane_count(&frame_info.raw.format);
		for (unsigned int k = 0; k < plane_count; k++)
		{
			const void *plane = NULL;
			size_t plane_len;
			res = mbuf_raw_video_frame_get_plane(
				frame, k, &plane, &plane_len);
			if (res < 0)
			{
				ULOG_ERRNO("mbuf_raw_video_frame_get_plane(%u)",
						   -res,
						   k);
				continue;
			}
			ULOGI("plane[%d]: addr=%p stride=%zu",
				  k,
				  plane,
				  frame_info.raw.plane_stride[k]);
			res = mbuf_raw_video_frame_release_plane(
				frame, k, plane);
			if (res < 0)
				ULOG_ERRNO(
					"mbuf_raw_video_frame_release_plane(%u)",
					-res,
					k);
		}

		vmeta_frame_unref(frame_meta);
		mbuf_raw_video_frame_unref(frame);
	}

	res = pdraw_vsink_stop(vsink);
	if (res < 0)
		ULOG_ERRNO("pdraw_vsink_stop", -res);
	/* media_info won't be valid after pdraw_vsink_stop() */

	ULOGI("%s", (status == EXIT_SUCCESS) ? "success!" : "failed!");
	exit(status);

	return 0;
}
