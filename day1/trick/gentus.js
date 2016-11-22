var tus = [];
tus.push({
    "cmd": "compile",
    "sourceId": 0,
    "langs": {
        "g++": [ "-O2", "-lm" ],
        "java": []
    }
});
for (var i = 1; i <= 15; ++ i) {
    tus.push({
        "cmd": "exec",
		"binId": 0,
		"timeLimit": "1000",
		"memLimit": "2048",
		"inputFile": "data/trick" + i + ".in"
    });
    tus.push({
        "cmd": "judge",
        "ansId": i * 2 - 1,
        "checker": "default",
        "inputFile": [ "data/trick" + i + ".in" ],
        "stdOutputFile": "data/trick" + i + ".ans"
    });
}
console.log(JSON.stringify(tus));
