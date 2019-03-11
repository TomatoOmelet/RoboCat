//
//  DeathLogManager.h
//  RoboCatAction
//
//  Created by Xavier Chua on 3/8/19.
//
class DeathLogManager
{
public:
    
    static void StaticInit();
    static std::unique_ptr< DeathLogManager >    sInstance;
    
    string GetEntry( );
    bool    RemoveEntry( );
    void    AddEntry( string playerName );
    
    bool    Write( OutputMemoryBitStream& inOutputStream ) const;
    bool    Read( InputMemoryBitStream& inInputStream );
    
    const deque< string >&    GetEntries()    const    { return mEntries; }
    
private:
    
    DeathLogManager();
    
    deque< string >    mEntries;
    
};
