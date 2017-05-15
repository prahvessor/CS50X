/*
*	web-audio-api-fproject.js
*	
*	Computer Science 50
*	Final Project	
*
*/


// audio context's vars
var context, audio, source, filters, analyserin, analyserout, gainNode, panner, filterLP; 
// analyser's vars
var ctxin, ctxout, canvasin, canvasout, fbc_array, bars, el;
// mp3 player's vars
var dir, ext, playlist, playlist_index, playlist_status, mylist;

// main function
function main() {
	window.AudioContext = window.AudioContext || window.webkitAudioContext;
	
	context = new AudioContext();
		console.log('1. Context created: ' + context);
	
	document.getElementById('audio_box').appendChild(audio);
	
	// init canvas
	canvasin = document.getElementById('analyser_render_in');
	canvasout = document.getElementById('analyser_render_out');
	ctxin = canvasin.getContext('2d');
	ctxout = canvasout.getContext('2d');
	
	
	// --- nodes
	source = context.createMediaElementSource(audio);
		console.log('2. Audio source initialised: ' + source);

	analyserin = context.createAnalyser();
		console.log('3. analyserin created: ' + analyserin);
	analyserout = context.createAnalyser();
		console.log('4. analyserout created: ' + analyserin);
	
	filterLP = context.createBiquadFilter();
		console.log('5. low pass filter created: ' + analyserin);
		
	filters = createFilters();
		console.log('6. Filter cascade created: ' + filters);
	
	gainNode = context.createGain();
		console.log('7. gainNode created: ' + gainNode);
	panner = context.createPanner();
		console.log('8. panner created: ' + panner);
		
	context.listener.setPosition(0, 0, 0);
	panner.setPosition(0, 0, 1);
	panner.panningModel = 'equalpower';
  
	filterLP.type = 'lowpass';
	filterLP.frequency.value = 5000;
	
	// --- play graph
	
	source.connect(analyserin);
	analyserin.connect(filters[0]);
	filters[filters.length - 1].connect(filterLP);
	filterLP.connect(gainNode);
	gainNode.connect(panner);
	panner.connect(analyserout);
	analyserout.connect(context.destination);
	
	frameLooperIn();
	frameLooperOut();
	eqValue();
	// input();
	console.log('main function loaded');
}

// ---- Mp3 player
function initMp3Player() {
	
	audio = new Audio();
	audio.controls = true;
	audio.volume = 0.15;
	audio.id = 'audio';
	
	dir = "audio/";
	playlist = ["Emiliana_-_Torrini_-_Jangle_drum","iBenji_-_Boom_feat_Talabun", 
				"Nirvana_-_Lithium_guitar only_Reading_30.08.92","The_White_Stripes_-_Seven_Nation_Army",
				"Rick_Astley_-_Never_Gonna_Give_You_Up","The_White_Stripes_-_Seven_Nation_Army"];
	playlist_index = 0;
	ext = ".mp3";
	
	playlist_status = document.getElementById("playlist_status");
	mylist = document.getElementById("mylist");
	
	audio.src = dir + playlist[0] + ext;
	audio.loop = false;
	audio.autoplay = false;
	
	//-----Listeners
	audio.addEventListener("ended", function(){ switchTrack();});
	mylist.addEventListener("change", changeTrack);
	
	//----- Current audio track on screen
	playlist_status.innerHTML = "Track: " + playlist[playlist_index] + ext;
	
	//----- Switch track in playlist
	function switchTrack() {
		if (playlist_index == (playlist.length - 1)) {
			playlist_index = 0;
		} else {
			playlist_index ++;
		}
		playlist_status.innerHTML = "Track: " + playlist[playlist_index] + ext;
		console.log('playing: ' + playlist[playlist_index]);
		audio.src = dir + playlist[playlist_index] + ext;
		audio.play();
	}
	
	//------ Change track by clicking 
	function changeTrack(event) {
		audio.src = dir + event.target.value + ext;
		playlist_status.innerHTML = "Track: " + event.target.value + ext;
		console.log('playing: ' + event.target.value + ext);
		audio.play();
	}
	console.log('Mp3Player function loaded');
}
	
// ----- equalizer filters
var createFilter = function (frequency) {
  var filter = context.createBiquadFilter();
     
	filter.type = 'peaking'; // filter type
	filter.frequency.value = frequency; // frequency
	filter.Q.value = 1; // Q-factor
	filter.gain.value = 0;
	
	return filter;
};
	
var createFilters = function () {
  var frequencies = [31, 63, 87, 125, 175, 250, 350, 500, 700, 1000, 1400, 2000, 2800, 4000, 5600, 8000, 11200, 16000],
	filters = frequencies.map(createFilter);
	
	filters.reduce(function (prev, curr) {
    prev.connect(curr);
    return curr;
  });
	
	return filters;
};

//----- low pass filter
var QUAL_MUL = 30;

function changeFrequency(element) {
	// Clamp the frequency between the minimum value (40 Hz) and half of the
	// sampling rate.
	var minValue = 40;
	var maxValue = context.sampleRate / 2;
	// Logarithm (base 2) to compute how many octaves fall in the range.
	var numberOfOctaves = Math.log(maxValue / minValue) / Math.LN2;
	// Compute a multiplier from 0 to 1 based on an exponential scale.
	var multiplier = Math.pow(2, numberOfOctaves * (element.value - 1.0));
	// Get back to the frequency value between min and max.
	filterLP.frequency.value = maxValue * multiplier;
	console.log('frequency: ' + filterLP.frequency.value);
};
	
function changeQuality(element) {
	filterLP.Q.value = element.value * QUAL_MUL;
	console.log('quality: ' + filterLP.Q.value);
};

function toggleFilter(element) {
	source.disconnect(0);
	analyserin.disconnect(0);
	filterLP.disconnect(0);
	filters[filters.length - 1].disconnect(0);
	gainNode.disconnect(0);
	panner.disconnect(0);
	analyserout.disconnect(0);
	// Check if we want to enable the filter.
	if (element.checked) {
    	// Connect through the filter.
		console.log('lowpass filter on');
		source.connect(analyserin);
		analyserin.connect(filters[0]);
		filters[filters.length - 1].connect(filterLP);
		filterLP.connect(gainNode);
		gainNode.connect(panner);
		panner.connect(analyserout);
		analyserout.connect(context.destination);
	} else {
    // Otherwise, connect directly.
		console.log('lowpass filter off');
		source.connect(analyserin);
		analyserin.connect(filters[0]);
		filters[filters.length - 1].connect(gainNode);
		gainNode.connect(panner);
		panner.connect(analyserout);
		analyserout.connect(context.destination);
	}
};

//--------- eq render
		
function frameLooperIn() {
	window.requestAnimationFrame(frameLooperIn);
	fbc_array = new Uint8Array(analyserin.frequencyBinCount);
	analyserin.getByteFrequencyData(fbc_array);
	ctxin.clearRect(0, 0, canvasin.width, canvasin.height);

	bars = 250;
	for (var i = 0; i < bars; i++) {
		if (i < 61) {
			ctxin.fillStyle = '#00ffff';
		} else if ((i >= 62) & (i < 123)) {
			ctxin.fillStyle = '#00ff00';
		} else if ((i >= 124) & (i < 185)) {
			ctxin.fillStyle = '#ffff00';
		} else if ((i >= 186) & (i < 250)) {
			ctxin.fillStyle = '#ff4300';
		}

		bar_x = i * 2;
		bar_width = 1;
		bar_height = -(fbc_array[i] / 6);
		ctxin.fillRect(bar_x, canvasin.height, bar_width, bar_height);
	}	
}
function frameLooperOut() {
	window.requestAnimationFrame(frameLooperOut);
	fbc_array = new Uint8Array(analyserout.frequencyBinCount);
	analyserout.getByteFrequencyData(fbc_array);
	ctxout.clearRect(0, 0, canvasout.width, canvasout.height);

	bars = 250;
	for (var i = 0; i < bars; i++) {
		if (i < 61) {
			ctxout.fillStyle = '#00ffff';
		} else if ((i >= 62) & (i < 123)) {
			ctxout.fillStyle = '#00ff00';
		} else if ((i >= 124) & (i < 185)) {
			ctxout.fillStyle = '#ffff00';
		} else if ((i >= 186) & (i < 250)) {
			ctxout.fillStyle = '#ff4300';
		}
	
		bar_x = i * 2;
		bar_width = 1;
		bar_height = -(fbc_array[i] / 6);
		ctxout.fillRect(bar_x, canvasout.height, bar_width, bar_height);
	}
}
		
//--- volume
	
function changeVolume(element) {
	var fraction = parseInt(element.value) / parseInt(element.max);
	// use an x*x curve (x-squared) since simple linear (x) does not
	// sound as good.
	gainNode.gain.value = fraction * fraction;
	console.log('volume: ' + gainNode.gain.value);
}
		
//---- panner
function changePan(event) {
	var x = document.getElementById('pan').valueAsNumber,
		y = 0,
		z = 1 - Math.abs(x),
		parent = this.parentNode;
		console.log('balance: ' + x,y,z);
		panner.setPosition(x,y,z);
}
		
//----- equalizer control
function eqValue() {
	console.log('listening events... ');
	for (var i = 0; i < 18 ; i++) {
		el = document.getElementById(i);
		el.addEventListener('change', function (e) {
												console.log(e.target.id + ': ' + e.target.value);
		                        				filters[e.target.id].gain.value = e.target.value;
												e.target.title = e.target.value;}
							, false);
	}
}

function input() {
	var arr = [	[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],													// default
				[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -3, -6, -6, -6, -8.4],											// classic
				[9, 6.6, 4.8, 2.1, 0.6, 0, 0, -1.2, -2.1, -2.7, -3.9, -4.2, -4.2, -4.2, -4.5, -4.2, 0, 0],				// dance
				[6.6, 6.6, 6.6, 6.6, 6.6, 4.5, 2.4, -0.6, -2.4, -1.8, -1.2, -0.6, 0.6, 1.5, 2.4, 3.9, 5.4, 9],			// headphones
				[3, 6, 5.1, 3.6, 1.8, -3.9, -5.1, -5.1, -2.1, 1.2, 4.5, 9, 3, -1.8, -4.5, -2.4, -0.6, 2.4],				// jazz
				[-4.2, -3, -1.5, 3.3, 4.5, 5.1, 4.8, 4.8, 5.1, 4.2, 3.6, 3, 2.4, 2.4, 2.1, 2.1, 1.8, 1.5],				// live
				[-1.8, 1.6, 3.9, 5.4, 5.4, 4.5, 2.1, 0.9, -0.6, -1.5, -1.5, -1.8, -2.1, -2.1, -2.7, -2.1, -2.1, -0.3],  // pop
				[0, 4.2, 5.1, 2.7, 0, -3.9, -4.5, -3.3, 0.3, 1.5, -1.8, -5.4, -0.6, 2.7, 4.5, 5.1, 2.4, 0], 			// rap
				[5.4, 4.5, 3.6, -3.9, -6.3, -6.9, -3.6, -2.7, -0.3, 2.1, 4.5, 6, 6.9, 7.5, 7.8, 7.8, 7.8, 8.1],			// rock
				[5.1, 4.8, 4.5, 3.9, 3.3, 1.5, -0.6, -2.4, -3.6, -3.3, -2.7, -1.8, -0.3, 1.5, 4.2, 5.1, 5.7, 5.4],		// techno
				[-4.8, -4.5, -3.9, -2.1, -0.3, 1.2, 1.8, 3.6, 6.6, 9, 6.9, 4.5, 2.4, 0.3, -0.9, -2.1, -2.7, -3]];		// vocal
	
	console.log('listening equalizer... ');
	document.getElementById('eqlist').oninput = function() {
            for(var i = 0; i < document.getElementById('equalizer').getElementsByTagName('input').length; i++){
                document.getElementById(i).value = arr[this.value][i];
                document.getElementById(i).title = arr[this.value][i];
                filters[i].gain.value = arr[this.value][i];
												// e.target.title = e.target.value;
                console.log('input' + i + ': ' + document.getElementById(i).value);
            }
        }
}
		
//--  
window.addEventListener("load", initMp3Player, false);
window.addEventListener("load", main, false);
window.addEventListener("load", input, false);