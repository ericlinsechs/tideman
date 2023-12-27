<h1 align="center">
<br>TIDEMAN</h1>

##  Overview

This repository provides a voting system that executes the [Tideman algorithm](https://en.wikipedia.org/wiki/Ranked_pairs). It collects candidate names and voter preferences, evaluates preferences. By recording and sorting preferences by victory strength, it eliminates potential cycles, eradicating bias. Ultimately, the system announces an unbiased election winner.

##  Getting Started

###  Installation

1. Clone the tideman repository:
```sh
git clone https://github.com/ericlinsechs/tideman.git
```

2. Change to the project directory:
```sh
cd tideman
```

3. Build the project:
```sh
make all
```

###  Running tideman

```sh
./tideman [candidate ...]
```

##  Acknowledgments

The source code for this project is based on the [Harvard University’s CS50 course](https://cs50.harvard.edu/x/2023/). You can find the problem description from the ["tideman" problem set](https://cs50.harvard.edu/x/2023/psets/3/tideman/).

