#include "Generator.h"

string Generator::genName()
{
    int length = this->genInt(4, 10);
    string name;
    bool isVowel = this->genInt(0, 1);
    int pos;
    for (int i = 0; i < length; i++)
    {
        if (isVowel)
        {
            pos = this->genInt(0, vowelsSize);
            name.push_back(vowels[pos]);
        }
        else
        {
            pos = this->genInt(0, consonantsSize);
            name.push_back(consonants[pos]);
        }
        isVowel = !isVowel;
    }
    name[0] = toupper(name[0]);
    return name.data();
}
string Generator::genString(size_t length)
{
    string res;
    int pos = 0;

    for (size_t i = 0; i < length; i++)
    {
        pos = this->genInt(0, charSetSize);
        res.push_back(charSet[pos]);
    }
    return res;
}
int Generator::genInt(int min, int max)
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}
void Generator::genUsersFile(int count, string resFile)
{
    stringstream os;

    for (int i = 0; i < count; i++)
    {
        os << setw(15) << left << this->genName() << " " << hasher.hashString(this->genString(100)) << " " << this->genInt(100, 100000) << endl;
    }
    file.writeFile(resFile, os);
}

void Generator::genTransactionsFile(int count, string usersFile, string resFile)
{

    stringstream usersSS = file.readFile(usersFile);
    vector<User> users;

    string name;
    string publicKey;
    int balance;

    while (usersSS >> name && usersSS >> publicKey && usersSS >> balance)
    {
        users.emplace_back(name, publicKey, balance);
    }

    int userCount = users.size();
    Transaction *tx;
    User *sender, *reciever;
    int amount;

    vector<Transaction> txs(count);

    for (int i = 0; i < count; i++)
    {
        sender = &users.at(this->genInt(0, userCount));
        reciever = &users.at(this->genInt(0, userCount));

        if (sender == reciever)
        {
            i--;
            continue;
        }
        amount = this->genInt(0, sender->getBalance());
        tx = &txs.at(i);
        tx->setTxID(this->hasher.hashString(sender->getPublicKey() + reciever->getPublicKey() + to_string(amount)));
        tx->addInput(sender->getPublicKey(), sender->getBalance());
        tx->addOutput(sender->getPublicKey(), sender->getBalance() - amount);
        tx->addOutput(reciever->getPublicKey(), amount);
    }

    stringstream os;

    for (auto &tx : txs)
    {
        os << tx.getTxID() << endl;
        for (auto &in : tx.getInputs())
            os << in.userPK << " " << in.amount << " ";
        os << endl;
        for (auto &out : tx.getOutputs())
            os << out.userPK << " " << out.amount << " ";
        os << endl;
    }
    file.writeFile(resFile, os);
};
