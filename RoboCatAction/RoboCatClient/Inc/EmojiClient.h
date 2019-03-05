class EmojiClient : public Emoji
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new EmojiClient() ); }

	virtual void		Read( InputMemoryBitStream& inInputStream ) override;
	
	void SetTexture(int index);
protected:
	EmojiClient();

private:

	SpriteComponentPtr	mSpriteComponent;
};