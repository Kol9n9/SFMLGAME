#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H


class Attribute
{
    public:
        Attribute(const int &level, const int &strength, const int &agility, const int &stamina);
        virtual ~Attribute();

        void setHP(const float &hp) {m_hp = hp;}
        void setEXP(const float &exp) {m_exp = exp;}

        void giveEXP(const float &exp) {m_exp += exp; updateAttribute();}

        void setStrength(const int &value) {m_strength = value;updateAttribute();}
        void setAgility(const int &value) {m_agility = value;updateAttribute();}
        void setStaming(const int &value) {m_stamina = value;updateAttribute();}
        void setLevel(const int &value) {m_level = value;updateAttribute();}

        int &getStrength(){return m_strength;}
        int &getAgility(){return m_agility;}
        int &getStaming(){return m_stamina;}
        int &getLevel(){return m_level;}

        float &getHP() {return m_hp;}
        float &getHPMax() {return m_hp_max;}
        float &getEXP() {return m_exp;}
        float &getEXPMax() {return m_exp_max;}
        float &getDamage() {return m_damage;}


    protected:

    private:
        int m_level;
        int m_strength;
        int m_agility;
        int m_stamina;
        float m_hp;
        float m_hp_max;
        float m_exp;
        float m_exp_max;
        float m_damage;

        void updateAttribute();
};

#endif // ATTRIBUTE_H
