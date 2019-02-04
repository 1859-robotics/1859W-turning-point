const fs = require("fs")
const config = require("./config.js")

// get .auton files
const autons = fs.readdirSync(config.path).filter(file => file.indexOf(".auton") !== -1)

let autonList = []

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

    console.log(metaData)
  }
})

console.log(autonList)

let def = ""

autonList.forEach()
