
// Variables
let m = 0;

let fRate = 5;

let modeButtons;

let simulSlider;
let manSlider;

const xClock = 200;
const y = 200;
const xDial = 550;
const xHalfDial = 775;

const mRadius = 130;
const hRadius = 50;

const xLed = 600;
const yLed = 200;

const xLed2 = 1000;

const rmLed = 140;
const rhLed = 60;
const rmLed2 = 100;

const xManSlider = 450;
const yManSlider =435;


const xSimulSlider = 450;
const ySimulSlider =480;

const xMode = 350;
const yMode = 470;

const xDigital = 80;
const yDigital = 520;



const xCanvas = 1200;
const yCanvas = 600;

const deltaMin = [315, 345,15, 45];
const deltaMinInv = [ 45, 15, 345, 315];


// toCartesian calculates point coordinates based on coordinates of
// center, radius and angle (in degrees)
function toCartesian(x, y, r, a) {
  // Get angle as radians
  const rad = a*(PI/180);
  // Convert coordinates
  const deltaX = r*cos(rad);
  const deltaY = r*sin(rad);
  // Return array of two cartesian coordinates: x and y
  return [x+deltaX, y+deltaY];
}
// drawDial draws Clock dial based on center coordinates, mRadius, length of dial
// mark and bool flag (true in case of half dial, false otherwise)
function drawDial(x0, y0, rs, delta, isHalf) {
  strokeWeight(1);
  stroke(0, 0, 0);
  for (let a = 0; a < 360; a += 30) {
    if (isHalf && (a > 90 && a < 270)) {
      continue ;
    }
    let startMark = toCartesian(x0, y0, rs, a);
    let endMark =  toCartesian(x0, y0, rs + delta, a);
    line(startMark[0],startMark[1],endMark[0],endMark[1]);
  }
}


function setRadioButtons() {
  modeButtons = createRadio();
  modeButtons.position(xMode,yMode);
  modeButtons.class('p5-radio')
  modeButtons.size(90);
  modeButtons.option('Manual');
  modeButtons.option('Realtime');
  modeButtons.option('Simulated');
  modeButtons.selected('Manual');  
 
}

function setSimulSlider(){
  simulSlider = createSlider(1,15,5);
  simulSlider.position(xSimulSlider, ySimulSlider);
  simulSlider.size(200,80)
}

function setManSlider(){
  manSlider = createSlider(0,719,0);
  manSlider.position(xManSlider, yManSlider);
  manSlider.size(720,80)
}


// Function 'setup' and 'draw' required by p5 lib.
function setup() {
  createCanvas(xCanvas, yCanvas);
  setSimulSlider();
  setManSlider();
  setRadioButtons();
}

function draw() {

  const minColor = [0,255,0];
  const hourColor = [255,255,255];
  const offColor = [147, 150, 149];
  
  const redColor = [255, 0, 0]
  const blueColor = [0, 102, 255]
  const cyanColor = [150,200,255]
  const purpleColor = [255,153,255]

  //background(220);
  background(204, 204, 255);
  // background(234, 218, 203);
  drawDial(xClock, y, mRadius + 15, 15, false); 
  drawDial(xDial, y, mRadius + 15, 15, false);  
  drawDial(xHalfDial, y, mRadius + 15, 15, true); 

  switch (modeButtons.value()) {
    case 'Manual':
       m = manSlider.value();
      break;
    case 'Simulated':
      m++;
      if (m === 720) {
        m = 0;
      }
      manSlider.value(m);
      break;
    case 'Realtime':
      let  date = new Date();
      let realHour = date.getHours();
      if (realHour >= 12) {
        realHour -=12;
      }
      let realMin = date.getMinutes();
      m = realHour*60 + realMin;
      manSlider.value(m);
      break;
    default:
      // impossible
  }
  
  let minutes = m%60;
  let modMin = minutes%5;
  let hours = m/60;

  let mAngle = minutes*6 - 90; // 360/60  
  if (mAngle < 0 ) {
    mAngle += 360;
  }
  let hAngle = hours*30 - 90 // 360/12
  if (hAngle < 0 ) {
    hAngle += 360;
  }
  // Digital Clock
  let sm = minutes.toFixed(0);  
  let sh = Math.floor(hours).toFixed(0);

  if (sh.length === 1 ) {
    sh = "0" + sh
  }
  if (sm.length === 1 ) {
    sm = "0" + sm
  }
  textSize(90);
  let simTime = sh + ":" + sm ;
  text(simTime,xDigital,yDigital);

  textSize(15);
  text("Time Mode:",xMode,yMode -10);

  noFill()
  strokeWeight(10);
  // Regular Clock with Hands
  stroke.apply(null, minColor); // Clock minutes hand (White)
  var newPos = toCartesian(xClock, y, mRadius, mAngle);
  line(xClock, y, newPos[0], newPos[1]);
  stroke.apply(null,hourColor);   // Hours hand (green)
  var newPosh = toCartesian(xClock, y, hRadius, hAngle);
  line(xClock, y, newPosh[0], newPosh[1]);

  // Full Dial Arcs Clock
  stroke.apply(null,offColor)
  circle(xDial, y, 2*mRadius)
  circle(xDial, y, 2*hRadius)
  stroke.apply(null,minColor); // Clock minutes  (White)
  arc(xDial, y, 2*mRadius, 2*mRadius, radians(270), radians(mAngle))
  stroke.apply(null,hourColor); // Clock hours (green)
  arc(xDial, y, 2*hRadius, 2*hRadius, radians(270), radians(hAngle))

  // Half Dial Arc Clock
  stroke.apply(null,offColor)
  arc(xHalfDial, y, 2*hRadius, 2*hRadius, radians(270), radians(90))
  arc(xHalfDial, y, 2*mRadius, 2*mRadius, radians(270), radians(90))
  stroke.apply(null, minColor); // Clock minutes (White)
  if (mAngle <= 90 ||  mAngle >= 270) {
    arc(xHalfDial, y, 2*mRadius, 2*mRadius, radians(270), radians(mAngle))
  } else {
    arc(xHalfDial, y, 2*mRadius, 2*mRadius, radians(180 - mAngle), radians(90))
  }
  stroke.apply(null, hourColor);// Clock hours (Green)
  if (hAngle < 90 ||  hAngle >= 270) {
    arc(xHalfDial, y, 2*hRadius, 2*hRadius, radians(270), radians(hAngle))
  } else {
    arc(xHalfDial, y, 2*hRadius, 2*hRadius, radians(180 - hAngle), radians(90))
  }
 
  // Half Dial Led Clock
  const bigLed = 15;
  
  mAngle = Math.floor(mAngle);
  hAngle = Math.floor(hAngle);

  const setLed = function(ledColor, weight,cX, cY, r,  a) {
    let dot = toCartesian(cX, cY, r, a);
    strokeWeight(weight);
    stroke(ledColor[0],ledColor[1],ledColor[2]);
    point(dot[0], dot[1]);    
  }
  
  const hourToAngle = function (h) {
    if (h < 6) {
      if (h < 3) {
        return (270 + h*30);
      } else {
        return (h-3)*30;
      }
    } else {
      let dh = h - 6
      if ( h <= 9 ) {
        return (90 - dh*30);
      } else {
        dh = h - 9;
        return (360 - dh*30)
      }
    }
  }
  const minToAngle = function (m) {
    if (m < 30) {
      if (m < 15) {
        return (270 + m*6);
      } else {
        return (m-15)*6;
      }
    } else {
      let dm = m - 30
      if ( m <= 45 ) {
        return (90 - dm*6);
      } else {
        dm = m - 45;
        return (360 - dm*6)
      }
    }
  }
  // Hours Led
  let i = 0;
  let max = 6;
  let ih = Math.floor(hours);
  if (ih >= 6) {
    i = 6;
    max = 12;
  }
  for (; i <= max ; i++) {
    let ha = hourToAngle(i);
    if (i <= ih) {
      setLed(hourColor, bigLed,xLed2, yLed, rhLed, ha);                  
    } else {
      setLed(offColor, bigLed,xLed2, yLed,rhLed, ha);          
    }
  }
  // Minutes Led
  let onColor = false;
  i = 0;
  max = 30;
  let im = Math.floor(minutes);
  if ( im >= 30 ) {
    i = 30;
    max = 60;
  }
  for (; i <= max ; i++) {
    md =i%5;  
    if ( md === 0 ){
      let ma = minToAngle(i);
      if (i <= im) {
        setLed(minColor, bigLed,xLed2, yLed, rmLed, ma);
        onColor = true;
      } else {
        if (onColor) {
          switch (modMin) {
            case 1:
              setLed(cyanColor, bigLed,xLed2, yLed,rmLed, ma); break;
            case 2:   
              setLed(purpleColor, bigLed,xLed2, yLed,rmLed, ma); break;
            case 3:
              setLed(redColor, bigLed,xLed2, yLed,rmLed, ma); break;
            case 4:
              setLed(blueColor, bigLed,xLed2, yLed,rmLed, ma); break;
            default:
              setLed(offColor, bigLed,xLed2, yLed,rmLed, ma);
          }    
        } else {
          setLed(offColor, bigLed,xLed2, yLed,rmLed, ma);   
        } 
        onColor = false; 
      }
    }

  }
 
  fRate = simulSlider.value();
  frameRate(fRate);
}