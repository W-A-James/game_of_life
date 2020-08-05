// TODO: have size be set by the user using a form/field
// TODO: create handlers for when the value inside the form/field changes

var numRows = 60;
var numCols = 60;
var board_deltas = [];
var isPaused = true;
var mouseDown = false; var stepPeriod = 75;
var drawing = true;
let container;
let parentDiv;

var Module = {
    onRuntimeInitialized: function() {
        // responsible for keeping grid square
        container = document.getElementById("container");
        // holds rows of div.grid-square elements
        parentDiv = document.getElementById("parent-div");
        initSim();
        main();
        // container which holds the parentDiv and is
        window.addEventListener("resize", () => {
            container.style.height = container.clientWidth + "px";
        });

        window.addEventListener("unload", () => {
            Module.free_board();
        });

        window.addEventListener("keydown", (event) => {
            // space or p
            if (event.keyCode === 80 || event.keyCode === 32) pauseSim();
            // r
            if (event.keyCode === 82) resetSim();
            // d
            if (event.keyCode === 68) startDrawing();
            // c
            if (event.keyCode === 67) startClearing();
        });
    }
};


/*
 * On window resize, resized all grid-squares
 * @param {Event} Event object
 */
function resizeGridRows(event) {
    const eventTarget = event.target;
    const children = eventTarget.children;
    for (let i = 0; i < children.length; i ++) {
        children[i].width = eventTarget.clientWidth / numCols + "px";
        children[i].height = eventTarget.clientHeight / numRows + "px";
    }
}

/**
 * Fills grid cell 'cellNum'
 *
 * @param {number} Cell number 
 */
function fillCell(cellNum) {
    const cell = document.getElementById(`grid-square-${cellNum}`);
    if (cell.classList.contains("grid-square-empty")) {
        cell.classList.remove("grid-square-empty");
        cell.classList.add("grid-square-full");
    }
    Module.fill_cell_(cellNum);
}

/**
 * Clears grid cell 'cellNum'
 *
 * @param {number} Cell number 
 */
function clearCell(cellNum) {
    const cell = document.getElementById(`grid-square-${cellNum}`);
    if (cell.classList.contains("grid-square-full")) {
        cell.classList.remove("grid-square-full");
        cell.classList.add("grid-square-empty");
    }
    Module.clear_cell_(cellNum);
}

/**
 * Fills or clears cell in target field of argument
 *
 * @param {Event} Event object
 */
function changeOnClick(event) {
    if (isPaused) {
    const cell = event.target;
    const cellNum = Number(event.target.id.split("-")[2]);
        if (drawing) {
            if (cell.classList.contains("grid-square-empty")) {
                cell.classList.remove("grid-square-empty");
                cell.classList.add("grid-square-full");
                Module.fill_cell_(cellNum);
            }
        }
        else {
            if (cell.classList.contains("grid-square-full")) {
                cell.classList.remove("grid-square-full");
                cell.classList.add("grid-square-empty");
                Module.clear_cell_(cellNum);
            }
        }
    }
}

/**
 * if game is paused set global mouseDown variable to true
 *
 */
function setMouseDown() {
    if (isPaused)
        mouseDown = true;
}

/**
 * if game is paused set global mouseDown variable to false 
 *
 */
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

            div.addEventListener("click", changeOnClick);
            div.addEventListener("mouseover", (event) => {
                if (mouseDown) changeOnClick(event);
            });
            row.append(div);
        }
    }

    document.addEventListener("mousedown", setMouseDown);
    document.addEventListener("mouseup", unsetMouseDown);

    const drawButton = document.getElementById("drawButton");
    const clearButton = document.getElementById("clearButton");
    drawButton.classList.add("selected");
    clearButton.classList.add("deselected");

    container.classList.add("pen_cursor");
    // Prevent default drga behaviour
    container.addEventListener("drag", (event) => {
        event.preventDefault();
    });

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

function selectDraw() {
    const drawButton = document.getElementById("drawButton");
    const clearButton = document.getElementById("clearButton");

    if (drawButton.classList.contains("deselected")) {
        drawButton.classList.remove("deselected");
        drawButton.classList.add("selected");
    }
    if (clearButton.classList.contains("selected")) {
        clearButton.classList.remove("selected");
        clearButton.classList.add("deselected");
    }
}

function selectClear() {
    const drawButton = document.getElementById("drawButton");
    const clearButton = document.getElementById("clearButton");

    if (drawButton.classList.contains("selected")) {
        drawButton.classList.remove("selected");
        drawButton.classList.add("deselected");
    }

    if (clearButton.classList.contains("deselected")) {
        clearButton.classList.remove("deselected");
        clearButton.classList.add("selected");
    }
}

function setDrawingCursor() {
    if (container.classList.contains("eraser_cursor")) {
        container.classList.remove("eraser_cursor");
        container.classList.add("pen_cursor");
    }
}

function setClearingCursor() {
    if (container.classList.contains("pen_cursor")) {
        container.classList.remove("pen_cursor");
        container.classList.add("eraser_cursor");
    }
}

function startDrawing() {
    drawing = true;
    selectDraw();
    setDrawingCursor();
}

function startClearing() {
    drawing = false;
    selectClear();
    setClearingCursor();
}

