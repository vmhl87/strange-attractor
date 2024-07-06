let x = 0.1, y = 0.1;

let c = [
	-1.7,
	1.3,
	-0.1,
	-1.21
];

function setup(){
	createCanvas(1200, 1200);
	background(210, 225, 230);
}

function draw(){
	stroke(70, 120, 255, 10);
	point(height/2 + height/2*x/2.5, height/2 + height/2*y/2.5);

	let nx = Math.sin(c[0]*y) + c[2]*Math.cos(c[0]*x),
		ny = Math.sin(c[1]*x) + c[3]*Math.cos(c[1]*y);

	x = nx; y = ny;
}
