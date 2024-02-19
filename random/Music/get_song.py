#~/usr/bin/env python3

from savify import Savify
from savify.types import Type, Format, Quality
from savify.utils import PathHolder
import sys

# see https://github.com/LaurenceRawlings/savify for details

SPOTIPY_ID="d0f20b415fc84979b9db1d5f5e6b3d04"
SPOTIPY_SECRET="237615044c914b1f94b514514d9a02ee"

if sys.argv[1] and sys.argv[2]:
    LINK=sys.argv[2]
    DOWNLOAD_PATH=f"/home/caleb/Music/MomsMusic/{sys.argv[1]}/"
else:
    print("ERROR in arguments enter the download path followed by the spotify link")
    exit()

if __name__ == '__main__':
    print(f"{LINK=}\n{DOWNLOAD_PATH=}")
    s = Savify(
            api_credentials=(SPOTIPY_ID, SPOTIPY_SECRET),
            quality=Quality.BEST,
            download_format=Format.MP3,
            path_holder=PathHolder(downloads_path=DOWNLOAD_PATH),
            skip_cover_art=False,
    )
    s.download(LINK, query_type=Type.TRACK)

