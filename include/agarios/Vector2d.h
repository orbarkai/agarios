class Vector2d {
	
	public:
        float x;
        float y;

    public:
        Vector2d();
        Vector2d(float x, float y);
        Vector2d(Vector2d& v);

    public:
        Vector2d& set(Vector2d& v);
        Vector2d& set(float x, float y);

        Vector2d& setAngle(float a);
        Vector2d& setAngleDeg(float a);	
        float getAngle();
        float getAngleDeg();
        Vector2d& rotateBy(float l);	
        
        Vector2d& add(Vector2d& v);
        Vector2d& subtract(Vector2d& v);
        Vector2d& add(float s);
        Vector2d& subtract(float s);
        Vector2d& multiply(float s);
        Vector2d& divide(float s);
        
        Vector2d& normalize();
        Vector2d& setLength(float l);
        float length();
        
        float dot(Vector2d& v);
        float cross(Vector2d& v);
        float distance(Vector2d v);
        Vector2d& pointTo(Vector2d& v);

    public:
        Vector2d operator+ (const Vector2d& v) const;
        Vector2d operator- (const Vector2d& v) const;
        Vector2d operator* (const float s) const;	
        float operator* (const Vector2d& v) const; //dot product
        float operator^ (const Vector2d& v) const; //cross product	
        Vector2d operator/ (const float s) const;
        Vector2d operator/ (const Vector2d& v) const;
        bool operator== (const Vector2d& v) const;
        void operator= (const Vector2d& v);
        void operator+= (const Vector2d& v);
        void operator-= (const Vector2d& v);
        void operator+= (const float s);
        void operator-= (const float s);
        void operator*= (const float s);	
        void operator/= (const float s);
        float operator[] (int i);
	
};