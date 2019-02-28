//
//  MilkServer.h
//  RoboCatActionServer
//
//  Created by Xavier Chua on 2/28/19.
//

class MilkServer : public Milk
{
public:
    static GameObjectPtr    StaticCreate() { return NetworkManagerServer::sInstance->RegisterAndReturn( new MilkServer() ); }
    void HandleDying() override;
    virtual bool        HandleCollisionWithCat( RoboCat* inCat ) override;
    
protected:
    MilkServer();
    
};
