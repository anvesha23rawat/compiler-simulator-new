const express = require("express");
const fs = require("fs");
const { exec } = require("child_process");

const app = express();
const PORT = 3000;

app.use(express.static(".")); // serve frontend.html
app.use(express.json());

// 🔹 TOKENIZE
app.post("/tokenize", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);

  exec(".\\lexer.exe", (error) => {
    if (error) {
      console.error("Lexer Error:", error.message);
      return res.json({ result: "Error during tokenization." });
    }

    const tokens = fs.readFileSync("tokens.txt", "utf8");
    res.json({ tokens });
  });
});

// 🔹 PARSE
app.post("/parse", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);

  exec(".\\parser.exe", (error) => {
    if (error) {
      console.error("Parser Error:", error.message);
      return res.json({ result: "Error during parsing." });
    }

    const parseTree = fs.readFileSync("parse.txt", "utf8");
    res.json({ result: parseTree });
  });
});

// 🔹 SEMANTIC
app.post("/semantic", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);

  exec(".\\semantic.exe", (error) => {
    if (error) {
      console.error("Semantic Error:", error.message);
      return res.json({ result: "Error during semantic analysis." });
    }

    const semanticOutput = fs.readFileSync("semantic.txt", "utf8");
    res.json({ result: semanticOutput });
  });
});

// 🔥 FULL PIPELINE (Run All)
app.post("/all", (req, res) => {
  fs.writeFileSync("Code.txt", req.body.code);

  exec(".\\lexer.exe && .\\parser.exe && .\\semantic.exe", (error) => {
    if (error) {
      console.error("Pipeline Error:", error.message);
      return res.json({ result: "Error running full pipeline." });
    }

    let output = "";

    output += "===== TOKENS =====\n";
    output += fs.readFileSync("tokens.txt", "utf8");

    output += "\n\n===== PARSE TREE =====\n";
    output += fs.readFileSync("parse.txt", "utf8");

    output += "\n\n===== SEMANTIC =====\n";
    output += fs.readFileSync("semantic.txt", "utf8");

    res.json({ result: output });
  });
});

// START SERVER
app.listen(PORT, () => {
  console.log(`Server running on http://localhost:${PORT}`);
});