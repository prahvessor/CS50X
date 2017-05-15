var context, filters=[], req, buffer, micsource, buffers=[], convolverNode, micvolume, analyserin, micfilters=[];   


context = new (window.AudioContext || window.webkitAudioContext || window.mozAudioContext || window.oAudioContext || window.msAudioContext)();
console.log('AudioContext created ' + context);

volumegain = context.createGain();

// --- init mic

function getmicrofonestream(){
 
	navigator.getUserMedia = (navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia);

	navigator.getUserMedia({ 
		audio: true, video: false }, 
		function (stream) {
			micsource = context.createMediaStreamSource(stream);
			console.log('micsource created');}, 
			function (e) {
				alert(e);
				console.log('micsource did\'t created');
			}
	);            
	
	micvolume = context.createGain();
	console.log('micvolume created: ' + micvolume);
	micvolume.gain.value = 0;
	
	// --- listener for mic value changes
	document.getElementById('micVolume').addEventListener('change',function (e) {
																			micvolume.gain.value = e.target.value;
																			console.log('micvolume value: ' + micvolume.gain.value);
																			}, false);
}
// ---- disable mic effects
function nomicefects(){
	convolverNode.disconnect(0);
	micsource.connect(micvolume);
	micvolume.connect(micfilters[0]);
	micfilters[filters.length - 1].connect(volumegain);
}

// --- enable mic effects
function initmicefects(i){ 
	
	micsource.connect(micvolume);
	console.log('micsource connected to micvolume');
		
	micvolume.connect(micfilters[0]);
	console.log('micvolume connected to micfilters[0]');
	micfilters[filters.length - 1].connect(analyserin);
	console.log('micfilters[13] connected to volumegain');
	console.log(filters[filters.length - 1] + 'filters[filters.' + filters.length - 1 + '] connected to analyserin');
}

function micEfects(){   

	createFilters(micfilters);

}

//----visualisation


function setupWebAudio() {
	analyserin = context.createAnalyser();
	console.log('analyserin created: ' + analyserin);
	
	filters[filters.length - 1].connect(analyserin);
	console.log(filters[filters.length - 1] + 'filters[filters.' + filters.length - 1 + '] connected to analyserin');
	
	analyserin.connect(context.destination);
	console.log('analyserin connected to destination');
}


function draw() {
	
	requestAnimationFrame(draw);
	var freqByteData = new Uint8Array(analyserin.frequencyBinCount);
	analyserin.getByteFrequencyData(freqByteData);
	canvasContext.clearRect(0, 0, canvas.width, canvas.height);

	// For each "bucket" in the frequency data, draw a line corresponding to its magnitude
	for (var i = 0; i < freqByteData.length; i++) {
		canvasContext.fillRect(i, canvas.height - freqByteData[i] * 0.3, 1, canvas.height + 20);
	}
}

// Basic setup for the canvas element, so we can draw something on screen
function setupDrawingCanvas() {
	d = document.getElementById('grafic');
	canvas = document.createElement('canvas');
	// 1024 is the number of samples that's available in the frequency data
	canvas.width = 530;
	// 255 is the maximum magnitude of a value in the frequency data
	canvas.height = 67;
	d.appendChild(canvas);
	canvasContext = canvas.getContext('2d');
	canvasContext.fillStyle = '#00BFFF';
}


// --- main equalizer

var createFilter = function(frequency) {
	var filter = context.createBiquadFilter();
	filter.type = "peaking";
	filter.frequency.value = frequency;
	filter.Q.value = 0.8;
	filter.gain.value = 0;
	return filter;
}

var createFilters = function(filtersarrays) {
	// var frequencies = [30,70, 170, 310, 600, 1000, 3000, 6000, 9000, 12000, 14000, 16000, 18000, 20000];
	var frequencies = [31, 63, 87, 125, 175, 250, 350, 500, 700, 1000, 1400, 2000, 2800, 4000, 5600];
    for (var i = 0; i <= 13; i++){
	filtersarrays[i] = createFilter(frequencies[i]);
	}
	 filtersarrays.reduce( function(prev, current){
		 prev.connect(current);
		 return current;});
}
	
var initEvents = function () {
	
	for ( i = 0; i <= 13; i++) {
		el = document.getElementById(i);
		el.addEventListener('change', function (e) {
													console.log(e.target.id + ': ' + e.target.value);
                                                    filters[e.target.id].gain.value = e.target.value;
													e.target.title = e.target.value;}
														, false);
	}
	
	//// event listener dly pegulyatora zvuka/////////////////////////
	document.getElementById('volumerange').addEventListener('change',function (e) {
																					volumegain.gain.value = e.target.value;
																					console.log('volume: ' + e.target.value);}
																					, false);
}