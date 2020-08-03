// TODO: have size be set by the user using a form/field
// TODO: create handlers for when the value inside the form/field changes

// TODO: add sidebar that has options to start drawing, start clearing
//       reset, or pause
// TODO: add keyboard event handler to start drawing, start clearing,
//       reset or pause

var numRows = 60;
var numCols = 60;
var board_deltas = [];
var isPaused = true;
var lastPause = Date.now();
var timeSincePause = 0;
var mouseDown = false;
var stepPeriod = 75;

var Module = {
    onRuntimeInitialized: function() {
        initSim();
        main();
    }
};

// container which holds the parentDiv and is responsible for keeping grid square
const container = document.getElementById("container");
// holds rows of div.grid-square elements
const parentDiv = document.getElementById("parent-div");

function resizeGridRows(event) {
    const eventTarget = event.target;
    const children = eventTarget.children;
    for (let i = 0; i < children.length; i ++) {
        children[i].width = eventTarget.clientWidth / numCols + "px";
        children[i].height = eventTarget.clientHeight / numRows + "px";
    }
}

function swapColour(cell) {
    const cellNum = Number(cell.id.split("-")[2]);
    if (cell.classList[1] == "grid-square-empty") {
        cell.classList.remove("grid-square-empty");
        cell.classList.add("grid-square-full");
        Module.fill_cell_(cellNum);
    }
    else {
        cell.classList.remove("grid-square-full");
        cell.classList.add("grid-square-empty");
        Module.clear_cell_(cellNum);
    }
}

function fillCell(cellNum) {
    const cell = document.getElementById(`grid-square-${cellNum}`);
    if (cell.classList[1] == "grid-square-empty") {
        cell.classList.remove("grid-square-empty");
        cell.classList.add("grid-square-full");
    }
    Module.fill_cell_(cellNum);
}

function clearCell(cellNum) {
    const cell = document.getElementById(`grid-square-${cellNum}`);
    if (cell.classList[1] == "grid-square-full") {
        cell.classList.remove("grid-square-full");
        cell.classList.add("grid-square-empty");
    }
    Module.clear_cell_(cellNum);
}

function swapOnClick(event) {
    if (isPaused) swapColour(event.target);
}

function setMouseDown() {
    if (isPaused)
        mouseDown = true;
}

function unsetMouseDown() {
    if (isPaused)
        mouseDown = false;
}

// draw empty board
function initSim() {
    container.style.height = container.clientWidth + "px";
    for (let i = 0; i < numRows; i++) {
        let row = document.createElement("div");
        row.classList.add("row");
        parentDiv.append(row);
        for (let j = 0; j < numCols; j++) {
            let div = document.createElement("div");
            div.id = `grid-square-${i*numCols+j}`;
            div.classList.add("grid-square");
            div.classList.add("grid-square-empty");
            // add handler
            div.addEventListener("click", swapOnClick);
            div.addEventListener("mousedown", setMouseDown);
            div.addEventListener("mouseup", unsetMouseDown);
            div.addEventListener("mouseover", (event) => {
                if (mouseDown) swapOnClick(event);
            });
            row.append(div);
        }
    }
    Module.init_board();
}


function resetSim() {
    let rows = document.getElementsByClassName("row");
    for (let i = 0; i < rows.length; i ++) {
        let cells = rows[i].children;
        for (let j = 0; j < cells.length; j++) {
            cells[j].classList.remove("grid-square-full");
            cells[j].classList.add("grid-square-empty");
        }
    }
    board_deltas = [];
    Module.reset_sim();

}

function pauseSim() {
    let pauseButton = document.getElementById("pauseButton");
    if (isPaused) { // play
        pauseButton.innerHTML = "Pause";
        isPaused= false;
    }

    else { // pause
        pauseButton.innerHTML = "Play";
        isPaused= true;
    }
    unsetMouseDown();
}

// iterate over board_deltas array and apply appropriate changes
// to displayed board
function updateBoard() {
    for (let i = 0; i < board_deltas.length; i++) {
        if (board_deltas[i].changeTo) {
            fillCell(board_deltas[i].cellNum);
        }
        else {
            clearCell(board_deltas[i].cellNum);
        }
    }
    board_deltas = [];
}


function main() {
    window.setInterval(()=> {
        if (!isPaused) {
            Module.step();
            updateBoard();
        }
    }, stepPeriod);
}

window.addEventListener("resize", () => {
    container.style.height = container.clientWidth + "px";
});

window.addEventListener("unload", () => {
    Module.free_board();
});

window.addEventListener("keydown", (event) => {
    // space
    if (event.keyCode === 32) pauseSim();
    // r
    if (event.keyCode === 82) resetSim();
});
