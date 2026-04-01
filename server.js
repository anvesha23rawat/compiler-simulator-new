const express = require("express");
const fs = require("fs");
const { exec } = require("child_process");
const app = express();
const PORT = 3000;

app.use(express.static("."));
app.use(express.json());

app.post("/tokenize", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);
  exec("lexer.exe", (error, stdout, stderr) => {
    if (error) {
      console.error("Tokenize Error:", error.message);
      return res.json({ result: "Error during tokenization." });
    }
    const tokens = fs.readFileSync("tokens.txt", "utf8");
    res.json({ tokens });
  });
});

app.post("/parse", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);
  exec("parser.exe", (error, stdout, stderr) => {
    if (error) {
      console.error("Parse Error:", error.message);
      return res.json({ result: "Error during parsing." });
    }
    const parseTree = fs.readFileSync("parse.txt", "utf8");
    res.json({ result: parseTree });
  });
});

app.post("/semantic", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);
  exec("semantic.exe", (error, stdout, stderr) => {
    if (error) {
      console.error("Semantic Error:", error.message);
      return res.json({ result: "Error during semantic analysis." });
    }
    const semanticOutput = fs.readFileSync("semantic.txt", "utf8");
    res.json({ result: semanticOutput });
  });
});


app.listen(PORT, () => console.log(`Server running on http://localhost:${PORT}`));
