/**
 * @file deck.h
 * @brief Deck and Card structures, as well as helper functions.
 */

#ifndef DECK_H
#define DECK_H

/**
 * @struct Card
 *
 * @brief Card structure. Structure used to keep information about an card.
 *
 * @var Card::suit
 *      The suit of the card.
 *      
 * @var Card::value
 *      The value of the card.
 */
struct Card {
    enum Suit suit;
    int value;
}

/**
 * @struct Deck
 *
 * @brief Deck structure. Structure used to keep pointers to the cards of the 
 *        deck.
 *
 * @var Deck::cards
 *      Pointer to the cards of the deck.
 */
struct Deck {
    struct Card *cards[DECK_SIZE];
}


#endif

