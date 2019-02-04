const fs = require("fs")
const config = require("./config.js")

// get .auton files
const autons = fs.readdirSync(config.path).filter(file => file.indexOf(".auton") !== -1)

console.log(autons)
