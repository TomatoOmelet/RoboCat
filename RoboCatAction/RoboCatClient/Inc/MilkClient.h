//
//  MilkClient.h
//  RoboCatActionClient
//
//  Created by Xavier Chua on 2/28/19.
//

class MilkClient : public Milk
{
public:
    static    GameObjectPtr    StaticCreate()        { return GameObjectPtr( new MilkClient() ); }
    
protected:
    MilkClient();
    
private:
    
    SpriteComponentPtr    mSpriteComponent;
};
