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

