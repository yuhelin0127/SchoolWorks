// C343 / Summer 2018
// Lab  03
// Name: Yuheng Lin
// Username: yuhelin


//an ADT for Card (with 52 cards, no Jokers)
public interface Card {

    //create a full deck of cards (with 52 cards)
    public void initialize();

    //draw a card, and return the card in the format of a string, e.g, 2S (2 of Spades)
    //the single letter representation for shapes:
    //S (spades), C (clubs), H (hearts) and D (diamonds)

    public String drawRandomCard();
}
