/* ======================================================
SFile: Vectors.h
SDate: 2020.11.25.
SRevision: S
SCreator: Gergely Zara
SNotice: S
======================================================*/

#define PI 3.14159265f

typedef float real32;
typedef double real64;

static int VectorsArrayCursor = 0;

typedef struct v3
{
	real32 x;
	real32 y;
	real32 z;
}Vector3;

static Vector3 V3UP = { 0, 1, 0 };
static v3 V3DOWN = { 0, -1, 0 };
static v3 V3RIGHT = { 1, 0, 0 };
static v3 V3LEFT = { -1, 0, 0 };
static v3 V3FORWARD = { 0, 0, 1 };
static v3 V3BACK = { 0, 0, -1 };

//inverse square root
inline float Q_rsqrt( float number )//inversesquareroot
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

//square root
inline float Q_sqrt( float number )//squareroot
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df + ( i >> 1 );               // what the fuck? 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

inline real32 distance(v3 A, v3 B)
{
	real32 Distance =
		(real32)sqrt
		(
			(real32)pow((A.x - B.x), 2)
			+ (real32)pow((A.y - B.y), 2)
			+ (real32)pow((A.z - B.z), 2)
		);
	return Distance;
}

inline real32 dot(v3 A, v3 B)
{
	real32 Result;
	Result = A.x * B.x + A.y * B.y + A.z * B.z ;
	return Result;
}

inline v3 cross(v3 V1, v3 V2)
{
	v3 Result;
	Result.x = (V1.y * V2.z) - (V1.z * V2.y);
	Result.y = (V1.z * V2.x) - (V1.x * V2.z);
	Result.z = (V1.x * V2.y) - (V1.y * V2.x);
	return Result;
}

inline v3 normal(v3 Vector, float VectorLength)
{
	v3 Result;
	Result.x = Vector.x / VectorLength;
	Result.y = Vector.y / VectorLength;
	Result.z = Vector.z / VectorLength;
	return Result;
}

bool32 v3IsEqual(v3 V1, v3 V2)
{
	if (V1.x == V2.x && V1.y == V2.y && V1.z == V2.z)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

v3 v3Add(v3 V1, v3 V2)
{
	struct v3 Result;
	Result.x = V1.x + V2.x;
	Result.y = V1.y + V2.y;
	Result.z = V1.z + V2.z;
	return Result;
}

v3 v3Sub(v3 V1, v3 V2)
{
	v3 Result;
	Result.x = V1.x - V2.x;
	Result.y = V1.y - V2.y;
	Result.z = V1.z - V2.z;
	return Result;
}

v3 v3Cross(v3 V1, v3 V2)
{
	struct v3 Result;
	Result.x = (V1.y * V2.z) - (V1.z * V2.y);
	Result.y = (V1.z * V2.x) - (V1.x * V2.z);
	Result.z = (V1.x * V2.y) - (V1.y * V2.x);
	return Result;
}

real64 v3Dot(v3 V1, v3 V2)
{
	v3 Res;
	Res.x = V1.x * V2.x;
	Res.y = V1.y * V2.y;
	Res.z = V1.z * V2.z;
	real64 Result = Res.x + Res.y + Res.z;
	return Result;
}

real32 DistanceBetweenTwoPoints(v3 thisPoint, v3 thatPoint)
{
	real64 Distance;
	Distance =
		sqrt(pow((thisPoint.x - thatPoint.x), 2)
		+ pow((thisPoint.y - thatPoint.y), 2)
		+ pow((thisPoint.z - thatPoint.z), 2));
	return (real32)Distance;
}

typedef struct quaternion
{//b,c,d are imaginary numbers -> b^2 = -1	
	real32 w;//scalar part for rotation around axis
	v3 v;

} Quaternion;

quaternion QtoRads(real32 w, struct v3 v)
{
	w = w / 360 * PI * 2;

	v3 VComponent =
	{
		(real32)v.x * (real32)sin(w / 2),
		(real32)v.y * (real32)sin(w / 2),
		(real32)v.z * (real32)sin(w / 2),
	};

	quaternion Result =
	{
		(real32)cos(w / 2),
		VComponent
	};

	return Result;
}

//https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
v3 QuaternionPointRotation(struct v3 Point, real32 Angle, struct v3 Axis)//v3 axisorientation
{
	v3 Result; // = {0,0,0};
	v3 VNull = {0,0,0};

	real32 AxDist = DistanceBetweenTwoPoints(VNull, Axis);
	v3 RotAxis = { Axis.x/AxDist, Axis.y / AxDist, Axis.z / AxDist };

	quaternion Q = QtoRads(Angle, RotAxis);

	//quaternion Q = {Angle, RotAxis};
	//quaternion InvQ = QInverse(Q);
	//Result = Q * P * InvQ;
	//Result = p + 2w(v × p) + 2(v ×(v × p));
	//t = 2 * cross(q.xyz, v)
	//v' = v + q.w * t + cross(q.xyz, t)

	v3 VxP = v3Cross(Q.v, Point);
	v3 VxPa = 
		{ (VxP.x * 2), (VxP.y * 2), (VxP.z * 2)};
	v3 VxPb = 
		{ (VxP.x * 2) * Q.w, (VxP.y * 2) * Q.w, (VxP.z *2) * Q.w };
	v3 PplusVxP = v3Add(Point, VxPb);
	v3 VxVxP = v3Cross(Q.v, VxPa);

	Result = v3Add
		(PplusVxP, VxVxP);
	return Result;
}