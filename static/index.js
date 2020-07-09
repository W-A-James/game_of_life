// TODO: ensure that resizing of the #container class works properly to ensure that
//       grid cells are always square
var Module = {
    onRuntimeInitialized: function() {
        Module.life()
    }
};

var numRows = 20;
var numCols = 20;
var boardState = [];

const parentDiv = document.getElementById("parent-div");
const container = document.getElementById("container");

function handleResize(event) {
    let eventTarget = event.target;
    let children = eventTarget.children;
    for (let i = 0; i < children.length; i ++) {
        children[i].width = eventTarget.clientWidth / numCols + "px";
        children[i].height = eventTarget.clientHeight / numRows + "px";
    }
}

function swapColour(cell) {
    if (cell.classList[1] == "grid-square-empty") {
        cell.classList.remove("grid-square-empty");
        cell.classList.add("grid-square-full");
    }
    else {
        cell.classList.remove("grid-square-full");
        cell.classList.add("grid-square-empty");
    }
}
function swapOnClick(event) {
    swapColour(event.target);
}

function initSim() {

    container.style.height = container.clientWidth + "px";
    for (let i = 0; i < numRows; i++) {
        boardState.push([]);
        let row = document.createElement("div");
        row.classList.add("row");
        parentDiv.append(row);
        for (let j = 0; j < numCols; j++) {
            boardState[i].push(false);
            let div = document.createElement("div");
            div.id = `grid-square-${i*numCols+j}`;
            div.classList.add("grid-square");
            div.classList.add("grid-square-empty");

            // add handler
            div.addEventListener("click", swapOnClick);
            row.append(div);
        }
    }
}


function resetSim() {
    let rows = document.getElementsByClassName("row");
    for (let i = 0; i < rows.length; i ++) {
        let cells = rows[i].children;
        for (let j = 0; j < cells.length; j++) {
            boardState[i][j] = false;
            cells[j].classList.remove("grid-square-full");
            cells[j].classList.add("grid-square-empty");
        }
    }
}

function update() {


}

window.addEventListener("load", () => {
    initSim();
});
