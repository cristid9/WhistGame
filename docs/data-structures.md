These are the basic data structures to be used in this project
======

### Card
* suit
* value

### Deck
* cards (array of Card)

### Player
* name
* cards (array of Card)
* isHuman

### Hand
* cards (array of Card)
* players (array of Player)

### Round
* trump
* hands (array of Hand)
* bids (array of int)
* pointsNumber (array of int)
* players (array of Player)
* deck
* roundType

### Game
* playersNumber
* rounds (array of Round)
* players (array of Player)
* gameType
