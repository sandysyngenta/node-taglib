>**Warning**
>Development Phase.
>macOS & linux support only.
> adding support for windows as well.

### Node.js binding for taglib. ``Still in development phase``.

##### TagLib is a ``C++`` library for reading and editing the metadata of several popular audio formats. To know more click [here](https://taglib.org/).

### How to use

```js
const NodeTagLib = require("node-taglib");

const exifData = NodeTagLib.getExifData("path_to_audio.mp3");

console.log(exifData);
/*
{
    album: "string",
    artist: "string",
    title: "string",
    genre: "string",
    comment: "string",
    track: "string",
    year: "string"
}
*/

------------
------------
------------
// How to update the exif data.
// You can omit the key which you don't want to update.
const success = NodeTagLib.setExifData("path_to_audio.mp3", {
    album: "my album",
    artist: "my artist"
});

if(success)
    console.log("exif data updated successfully...");

------------
------------
------------
// How to save the cover Art Image from the file.
// This will create a new file & save cover image to the destination.
const success = NodeTagLib.saveCoverArt("path_to_audio.mp3", "new_cover_art.jpeg");

if(success)
    console.log("conver image extracted...");

------------
------------
------------
// Get the cover image data (UInt8Array)
const buffer = NodeTagLib.getCoverArt("path_to_audio.mp3");

```

>**Note**
>Don't worry about file & folder structure for now. All will be fixed in near future.

### Bindings to be written

- [x] Get exif data.
- [x] Set / Update exif data.
- [x] Save cover image.
- [x] Get cover image data (bytes).
- [ ] many more features coming soon...