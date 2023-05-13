const nodeTaglib = require("bindings")("node_taglib");

const demoFile = "my_song.mp3";

const currentExif = nodeTaglib.getExifData(demoFile);

console.log("current exif: ", currentExif);

console.log("updating...");

nodeTaglib.setExifData(demoFile, {
    artist: "sandeep",
    album: "sandy's album",
    year: "1999"
});

const updatedExif = nodeTaglib.getExifData(demoFile);

console.log("updated exif: ", updatedExif);