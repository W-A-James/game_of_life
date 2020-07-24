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

navGhost.addEventListener("mouseover", () => {
    switch (navStatus) {
        case NAV_STAT.SLIDING_IN:
            clearInterval(navSlideInInterval);
            navSlideOutInterval = window.setInterval(
                () -> {
                
                }, interval_ms
            )
            break;
        case NAV_STAT.IN:
            break;
        case NAV_STAT.SLIDING_OUT:
            break;
        case NAV_STAT.OUT:
            break;
    }
})

