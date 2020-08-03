const navGhost = document.getElementById("nav_ghost");
const nav = document.getElementById("nav");

const NAV_STAT = {
    SLIDING_IN: 0,
    IN: 1,
    SLIDING_OUT: 2,
    OUT: 3
}

let navSlideInInterval;
let navSlideOutInterval;
const interval_ms = 100;

let navStatus = NAV_STAT.IN;
function slideNavOut() {
}

function slideNavIn() {
}

navGhost.addEventListener("mouseover", (event) => {
    console.log("mouseover!");
    switch (navStatus) {
        case NAV_STAT.SLIDING_IN:
        case NAV_STAT.IN:
            //clearInterval(navSlideInInterval);
            //navSlideOutInterval = window.setInterval(
                //() -> {
                    // start sliding out
                    //nav.style.left = parseInt(nav.style.left) + 5 + "px";
                    // if fully out, do nothing
                //}, interval_ms
            //)
            break;
        case NAV_STAT.SLIDING_OUT:
        case NAV_STAT.OUT:
            //clearInterval(navSlideOutInterval);
            //navSlideInInterval = window.setInterval(
                //() => {
                    // start sliding in 
                    // if fully in, do nothing
                //}, interval_ms
            //)
            break;
            break;
    }
})

