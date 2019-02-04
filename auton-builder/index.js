const fs = require("fs")
const config = require("./config.js")

// get .auton files
const autons = fs.readdirSync(config.path).filter(file => file.indexOf(".auton") !== -1)

let autonList = []
let autonLists = {
  "BLUE_A": [],
  "BLUE_B": [],
  "RED_A": [],
  "RED_B": []
}

autons.forEach(file => {
  const auton = fs.readFileSync(config.path + file, "utf8")
  const meta = auton.match(/#meta .*/g) // get meta directives
  let script = auton.replace(/#meta .*/g, "")

  let metaData = {}

  if(!meta) {
    console.log("auton file must contain meta data | " + file)
  } else {
    meta.forEach(m => { // extract meta data
      metaData[m.split(" ")[1]] = m.split(" ")[2]
    })

    autonList.push({
      ...metaData,
      content: script
    })

    if(config.validTiles.includes(metaData.tile)) {
      autonLists[metaData.tile].push(metaData.name)
    } else {
      console.log("auton file must contain a valid start tile | " + file)
    }

    console.log(metaData)
  }
})


let def = `
#ifndef AUTON_DEF_HPP
#define AUTON_DEF_HPP

// tile names
#define TILE_BLUE_A 1
#define TILE_BLUE_B 2
#define TILE_RED_A 3
#define TILE_RED_B 4

`

// create list of autons for a square
Object.entries(autonLists).forEach(list => {
  def += "#define AUTON_OPTIONS_" + list[0] + " " + list[1].reduce((acc, cur, i) => {
    if(i !== 0) return acc + ` \\n ` + `"` + cur + `"`
    else return `"` + cur + `"`
  }, "") + "\n"
})

console.log(def)
