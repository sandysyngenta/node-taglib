const nodeTaglib = require("bindings")("node_taglib");

const demoFile = "my_song.mp3";

console.log(nodeTaglib.getExifData(demoFile));