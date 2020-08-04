let navGhost;
let nav;
let navIsMoving = false;
let navIn = false;
const navWidth = parseInt(getComputedStyle(document.documentElement).getPropertyValue('--nav-width'));

window.addEventListener("load", ()=>{
    navGhost = document.getElementById("nav_ghost");
    nav = document.getElementById("nav");

    const interval_ms = 100;

    navGhost.addEventListener("mouseover", (event) => {
        if (!navIsMoving) {
            navIsMoving = true;
            if (navIn) {
                nav.classList.remove("movingIn");
                nav.classList.add("movingOut");
                navIn = false;    
            }
            else {
                nav.classList.remove("movingOut");
                nav.classList.add("movingIn");
                navIn = true;
            }
        }
    });

    window.setInterval(() => { 
        let view_width = window.innerWidth;
        let left_ = window.getComputedStyle(nav, null).getPropertyValue("left");
        let float_left = Math.round(100*parseFloat(left_)/view_width);
        if (navIn) {
            if (float_left <= -navWidth - 1) navIsMoving = false;
        }
        else {
            if (float_left >= -1) navIsMoving = false;
        }
    }, 50);
});

