#include "joypackage.h"
#include "engine.h"

Shit::Shit(Suit suit, int number):BasicCard(suit, number){
    setObjectName("shit");

    target_fixed = true;
}

QString Shit::getSubtype() const{
    return "disgusting_card";
}

void Shit::onMove(const CardMoveStruct &move) const{
    ServerPlayer *from = move.from;
    if(from && move.from_place == Player::Hand &&
       from->getRoom()->getCurrent() == move.from
       && (move.to_place == Player::DiscardedPile || move.to_place == Player::Special)
       && move.to == NULL
       && from->isAlive()){

        DamageStruct damage;
        damage.from = damage.to = from;
        damage.card = this;

        switch(getSuit()){
        case Club: damage.nature = DamageStruct::Thunder; break;
        case Heart: damage.nature = DamageStruct::Fire; break;
        default:
            damage.nature = DamageStruct::Normal;
        }

        from->getRoom()->damage(damage);
    }
}

bool Shit::HasShit(const Card *card){
    if(card->isVirtualCard()){
        QList<int> card_ids = card->getSubcards();
        foreach(int card_id, card_ids){
            const Card *c = Sanguosha->getCard(card_id);
            if(c->objectName() == "shit")
                return true;
        }

        return false;
    }else
        return card->objectName() == "shit";
}

// -----------  Deluge -----------------

Deluge::Deluge(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("deluge");

    judge.pattern = QRegExp("(.*):(.*):([AK])");
    judge.good = false;
    judge.reason = objectName();
}

void Deluge::takeEffect(ServerPlayer *target) const{
    QList<const Card *> cards = target->getCards("he");

    Room *room = target->getRoom();
    int n = qMin(cards.length(), target->aliveCount());
    if(n == 0)
        return;

    qShuffle(cards);
    cards = cards.mid(0, n);

    QList<int> card_ids;
    foreach(const Card *card, cards){
        card_ids << card->getEffectiveId();
        room->throwCard(card);
    }

    room->fillAG(card_ids);

    QList<ServerPlayer *> players = room->getOtherPlayers(target);
    players << target;
    players = players.mid(0, n);
    foreach(ServerPlayer *player, players){
        if(player->isAlive()){
            int card_id = room->askForAG(player, card_ids, false, "deluge");
            card_ids.removeOne(card_id);

            room->takeAG(player, card_id);
        }
    }

    foreach(int card_id, card_ids)
        room->takeAG(NULL, card_id);

    room->broadcastInvoke("clearAG");
}

// -----------  Typhoon -----------------

Typhoon::Typhoon(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("typhoon");

    judge.pattern = QRegExp("(.*):(diamond):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Typhoon::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();

    QList<ServerPlayer *> players = room->getOtherPlayers(target);
    foreach(ServerPlayer *player, players){
        if(target->distanceTo(player) == 1){
            int discard_num = qMin(6, player->getHandcardNum());
            if(discard_num == 0)
                room->setEmotion(player, "good");
            else{
                room->setEmotion(player, "bad");
                room->broadcastInvoke("animate", "typhoon:" + player->objectName());
                room->broadcastInvoke("playAudio", "typhoon");

                room->askForDiscard(player, objectName(), discard_num);
            }

            room->getThread()->delay();
        }
    }
}

// -----------  Earthquake -----------------

Earthquake::Earthquake(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("earthquake");

    judge.pattern = QRegExp("(.*):(club):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Earthquake::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();
    QList<ServerPlayer *> players = room->getAllPlayers();
    foreach(ServerPlayer *player, players){
        if(target->distanceTo(player) <= 1){
            if(player->getEquips().isEmpty()){
                room->setEmotion(player, "good");
            }else{
                room->setEmotion(player, "bad");
                room->broadcastInvoke("playAudio", "earthquake");
                player->throwAllEquips();
            }

            room->getThread()->delay();
        }
    }
}

// -----------  Volcano -----------------

Volcano::Volcano(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("volcano");

    judge.pattern = QRegExp("(.*):(heart):([2-9])");
    judge.good = false;
    judge.reason = objectName();
}

void Volcano::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();

    QList<ServerPlayer *> players = room->getAllPlayers();

    foreach(ServerPlayer *player, players){
        int point = 2 - target->distanceTo(player);
        if(point >= 1){
            DamageStruct damage;
            damage.card = this;
            damage.damage = point;
            damage.to = player;
            damage.nature = DamageStruct::Fire;

            room->broadcastInvoke("playAudio", "volcano");
            room->damage(damage);
        }
    }
}

// -----------  MudSlide -----------------
MudSlide::MudSlide(Card::Suit suit, int number)
    :Disaster(suit, number)
{
    setObjectName("mudslide");

    judge.pattern = QRegExp("(.*):(spade|club):([AK47])");
    judge.good = false;
    judge.reason = objectName();
}

void MudSlide::takeEffect(ServerPlayer *target) const{
    Room *room = target->getRoom();
    QList<ServerPlayer *> players = room->getAllPlayers();
    int to_destroy = 4;
    foreach(ServerPlayer *player, players){
        room->broadcastInvoke("playAudio", "mudslide");

        QList<const Card *> equips = player->getEquips();
        if(equips.isEmpty()){
            DamageStruct damage;
            damage.card = this;
            damage.to = player;
            room->damage(damage);
        }else{
            int i, n = qMin(equips.length(), to_destroy);
            for(i=0; i<n; i++){
                room->throwCard(equips.at(i));
            }

            to_destroy -= n;
            if(to_destroy == 0)
                break;
        }
    }
}

class GrabPeach: public TriggerSkill{
public:
    GrabPeach():TriggerSkill("grab_peach"){
        events << CardUsed;
    }

    virtual bool triggerable(const ServerPlayer *) const{
        return true;
    }

    virtual bool trigger(TriggerEvent , ServerPlayer *player, QVariant &data) const{
        CardUseStruct use = data.value<CardUseStruct>();
        if(use.card->inherits("Peach")){
            Room *room = player->getRoom();
            QList<ServerPlayer *> players = room->getOtherPlayers(player);

            foreach(ServerPlayer *p, players){
                if(p->getOffensiveHorse() == parent() &&
                   p->askForSkillInvoke("grab_peach", data))
                {
                    room->throwCard(p->getOffensiveHorse());
                    room->playCardEffect(objectName(), p->getGeneral()->isMale());
                    p->obtainCard(use.card);

                    return true;
                }
            }
        }

        return false;
    }
};

Monkey::Monkey(Card::Suit suit, int number)
    :OffensiveHorse(suit, number)
{
    setObjectName("monkey");

    grab_peach = new GrabPeach;
    grab_peach->setParent(this);
}

void Monkey::onInstall(ServerPlayer *player) const{
    player->getRoom()->getThread()->addTriggerSkill(grab_peach);
}

void Monkey::onUninstall(ServerPlayer *player) const{
    player->getRoom()->getThread()->removeTriggerSkill(grab_peach);
}

QString Monkey::getEffectPath(bool ) const{
    return "audio/card/common/monkey.ogg";
}

JoyPackage::JoyPackage()
    :Package("joy")
{
    QList<Card *> cards;

    cards << new Shit(Card::Club, 1)
            << new Shit(Card::Heart, 8)
            << new Shit(Card::Diamond, 13);

    cards << new Deluge(Card::Spade, 1)
            << new Typhoon(Card::Spade, 4)
            << new Earthquake(Card::Club, 10)
            << new Volcano(Card::Heart, 13)
            << new MudSlide(Card::Heart, 7);

    cards << new Monkey(Card::Diamond, 13);

    foreach(Card *card, cards)
        card->setParent(this);

    type = CardPack;
}

ADD_PACKAGE(Joy);
