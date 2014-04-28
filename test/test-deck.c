#include <deck.h>
#include <constants.h>
#include <errors.h>

#include <cutter.h>

void test_deck_createCard()
{
    struct Card *card;
    cut_assert_equal_pointer(NULL, deck_createCard(SuitEnd, VALUES[0]));
    cut_assert_equal_pointer(NULL, deck_createCard(DIAMONDS, -1));
    cut_assert_equal_pointer(NULL, deck_createCard(SuitEnd, -1));

    for (int i = 0; i < SuitEnd; i++)
        for (int j = 0; VALUES[j] != -1; j++) {
            card = deck_createCard(i, VALUES[j]);
            cut_assert_equal_int(card->suit, i);
            cut_assert_equal_int(card->value, VALUES[j]);
        }

    deck_deleteCard(card);
}

void test_deck_deleteCard()
{
    struct Card *card = deck_createCard(DIAMONDS, VALUES[0]);
    cut_assert_equal_int(CARD_NULL, deck_deleteCard(NULL));
    cut_assert_equal_int(NO_ERROR, deck_deleteCard(card));
}

void test_deck_createDeck()
{
    struct Deck *deck;
    cut_assert_equal_pointer(NULL, deck_createDeck(MAX_GAME_PLAYERS + 1));
    cut_assert_equal_pointer(NULL, deck_createDeck(MIN_GAME_PLAYERS - 1));

    for (int i = MIN_GAME_PLAYERS; i <= MAX_GAME_PLAYERS; i++) {
        deck = deck_createDeck(i);
        int check = 0;
        if (deck == NULL)
            check++;
        cut_assert_equal_int(0, check);

        int k = 0;
        while (deck->cards[k] != NULL)
            k++;
        cut_assert_equal_int((double)MAX_CARDS, (double)++k / i);
        
        int duplicates = 0;
        for (int j = 0; j < DECK_SIZE; j++)
            for (k = 0; k < DECK_SIZE; k++)
                if (k != j && deck->cards[k] != NULL && deck->cards[j] != NULL
                    && deck->cards[k]->suit == deck->cards[j]->suit &&
                    deck->cards[k]->value == deck->cards[j]->value)
                    duplicates++;
        cut_assert_equal_int(0, duplicates);
    }

}

