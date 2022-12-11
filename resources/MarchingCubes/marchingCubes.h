#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H

#include <iostream>

#include "MarchingCubes/cube_domain.h"
#include "mesh.h"

namespace MC {

    unsigned long long int mcConfig[] = {
		0ULL, 33793ULL, 36945ULL, 159668546ULL,
		18961ULL, 144771090ULL, 5851666ULL, 595283255635ULL,
		20913ULL, 67640146ULL, 193993474ULL, 655980856339ULL,
		88782242ULL, 736732689667ULL, 797430812739ULL, 194554754ULL,
		26657ULL, 104867330ULL, 136709522ULL, 298069416227ULL,
		109224258ULL, 8877909667ULL, 318136408323ULL, 1567994331701604ULL,
		189884450ULL, 350847647843ULL, 559958167731ULL, 3256298596865604ULL,
		447393122899ULL, 651646838401572ULL, 2538311371089956ULL, 737032694307ULL,
		29329ULL, 43484162ULL, 91358498ULL, 374810899075ULL,
		158485010ULL, 178117478419ULL, 88675058979ULL, 433581536604804ULL,
		158486962ULL, 649105605635ULL, 4866906995ULL, 3220959471609924ULL,
		649165714851ULL, 3184943915608436ULL, 570691368417972ULL, 595804498035ULL,
		124295042ULL, 431498018963ULL, 508238522371ULL, 91518530ULL,
		318240155763ULL, 291789778348404ULL, 1830001131721892ULL, 375363605923ULL,
		777781811075ULL, 1136111028516116ULL, 3097834205243396ULL, 508001629971ULL,
		2663607373704004ULL, 680242583802939237ULL, 333380770766129845ULL, 179746658ULL,
		42545ULL, 138437538ULL, 93365810ULL, 713842853011ULL,
		73602098ULL, 69575510115ULL, 23964357683ULL, 868078761575828ULL,
		28681778ULL, 713778574611ULL, 250912709379ULL, 2323825233181284ULL,
		302080811955ULL, 3184439127991172ULL, 1694042660682596ULL, 796909779811ULL,
		176306722ULL, 150327278147ULL, 619854856867ULL, 1005252473234484ULL,
		211025400963ULL, 36712706ULL, 360743481544788ULL, 150627258963ULL,
		117482600995ULL, 1024968212107700ULL, 2535169275963444ULL, 4734473194086550421ULL,
		628107696687956ULL, 9399128243ULL, 5198438490361643573ULL, 194220594ULL,
		104474994ULL, 566996932387ULL, 427920028243ULL, 2014821863433780ULL,
		492093858627ULL, 147361150235284ULL, 2005882975110676ULL, 9671606099636618005ULL,
		777701008947ULL, 3185463219618820ULL, 482784926917540ULL, 2900953068249785909ULL,
		1754182023747364ULL, 4274848857537943333ULL, 13198752741767688709ULL, 2015093490989156ULL,
		591272318771ULL, 2659758091419812ULL, 1531044293118596ULL, 298306479155ULL,
		408509245114388ULL, 210504348563ULL, 9248164405801223541ULL, 91321106ULL,
		2660352816454484ULL, 680170263324308757ULL, 8333659837799955077ULL, 482966828984116ULL,
		4274926723105633605ULL, 3184439197724820ULL, 192104450ULL, 15217ULL,
		45937ULL, 129205250ULL, 129208402ULL, 529245952323ULL,
		169097138ULL, 770695537027ULL, 382310500883ULL, 2838550742137652ULL,
		122763026ULL, 277045793139ULL, 81608128403ULL, 1991870397907988ULL,
		362778151475ULL, 2059003085103236ULL, 2132572377842852ULL, 655681091891ULL,
		58419234ULL, 239280858627ULL, 529092143139ULL, 1568257451898804ULL,
		447235128115ULL, 679678845236084ULL, 2167161349491220ULL, 1554184567314086709ULL,
		165479003923ULL, 1428768988226596ULL, 977710670185060ULL, 10550024711307499077ULL,
		1305410032576132ULL, 11779770265620358997ULL, 333446212255967269ULL, 978168444447012ULL,
		162736434ULL, 35596216627ULL, 138295313843ULL, 891861543990356ULL,
		692616541075ULL, 3151866750863876ULL, 100103641866564ULL, 6572336607016932133ULL,
		215036012883ULL, 726936420696196ULL, 52433666ULL, 82160664963ULL,
		2588613720361524ULL, 5802089162353039525ULL, 214799000387ULL, 144876322ULL,
		668013605731ULL, 110616894681956ULL, 1601657732871812ULL, 430945547955ULL,
		3156382366321172ULL, 7644494644932993285ULL, 3928124806469601813ULL, 3155990846772900ULL,
		339991010498708ULL, 10743689387941597493ULL, 5103845475ULL, 105070898ULL,
		3928064910068824213ULL, 156265010ULL, 1305138421793636ULL, 27185ULL,
		195459938ULL, 567044449971ULL, 382447549283ULL, 2175279159592324ULL,
		443529919251ULL, 195059004769796ULL, 2165424908404116ULL, 1554158691063110021ULL,
		504228368803ULL, 1436350466655236ULL, 27584723588724ULL, 1900945754488837749ULL,
		122971970ULL, 443829749251ULL, 302601798803ULL, 108558722ULL,
		724700725875ULL, 43570095105972ULL, 2295263717447940ULL, 2860446751369014181ULL,
		2165106202149444ULL, 69275726195ULL, 2860543885641537797ULL, 2165106320445780ULL,
		2280890014640004ULL, 11820349930268368933ULL, 8721082628082003989ULL, 127050770ULL,
		503707084675ULL, 122834978ULL, 2538193642857604ULL, 10129ULL,
		801441490467ULL, 2923200302876740ULL, 1443359556281892ULL, 2901063790822564949ULL,
		2728339631923524ULL, 7103874718248233397ULL, 12775311047932294245ULL, 95520290ULL,
		2623783208098404ULL, 1900908618382410757ULL, 137742672547ULL, 2323440239468964ULL,
		362478212387ULL, 727199575803140ULL, 73425410ULL, 34337ULL,
		163101314ULL, 668566030659ULL, 801204361987ULL, 73030562ULL,
		591509145619ULL, 162574594ULL, 100608342969108ULL, 5553ULL,
		724147968595ULL, 1436604830452292ULL, 176259090ULL, 42001ULL,
		143955266ULL, 2385ULL, 18433ULL, 0ULL,
	};

    typedef struct mcVec3i
	{
	public:
		union 
		{
			unsigned int v[3];
			struct 
			{
				unsigned int x, y, z;
			};
		};
		inline unsigned int& operator[](int i) { return v[i]; }
	} mcVec3i;

    int index3DTo1D(int x, int y, int z, int size)
    {
        return size * size * (z%2) + size * y + x; 
    }

    void addEdge(mcVec3i *edgeIndexMap, Mesh &mesh, float va, float vb, int axis, int x, int y, int z, int size)
    {
        if((va < 0) == (vb < 0))
            return;
        
        Vector3 v(x, y, z);
        v[axis] += va/(va - vb);

        edgeIndexMap[index3DTo1D(x, y, z, size)][axis] = mesh.vertices.size();
        mesh.vertices.push_back(v);
        Vector3 normal(0,0,0);
        mesh.normals.push_back(normal);

        // std::cout << "Vertex: " << v.x << " " << v.y << " " << v.z << std::endl;  
    }

    void calculateNormal(Mesh &mesh, int i, int j, int k)
    {
        Vector3 va = mesh.vertices[i];
        Vector3 vb = mesh.vertices[j];
        Vector3 vc = mesh.vertices[k];

        Vector3 ab = va - vb;
        Vector3 cb = vc - vb;

        Vector3 normal = ab.cross(ab, cb);
        // std::cout << "normals: " << normal.length() << std::endl;

        mesh.normals[i] += normal;
        mesh.normals[j] += normal;
        mesh.normals[k] += normal;
    }


    void MarchingCubes(CubeDomain domain, Mesh &mesh, float isoLevel)
    {
        float unitCubeVertices[8] = {0};
        unsigned int edgeIndices[12];
        mcVec3i* edgeIndexMap = new mcVec3i[domain.size* domain.size * 2];

        for(int z = 0; z < domain.size - 1; z++)
        {
            for(int y = 0; y < domain.size - 1; y++)
            {
                for(int x = 0; x < domain.size - 1; x++)
                {
                    // std::cout << x << " " << y << " " << z << "top" << std::endl;

                    unitCubeVertices[0] = domain.domain[x][y][z];
                    unitCubeVertices[1] = domain.domain[x+1][y][z];
                    unitCubeVertices[2] = domain.domain[x][y+1][z];
                    unitCubeVertices[3] = domain.domain[x+1][y+1][z];
                    unitCubeVertices[4] = domain.domain[x][y][z+1];
                    unitCubeVertices[5] = domain.domain[x][y+1][z];
                    unitCubeVertices[6] = domain.domain[x][y+1][z+1];
                    unitCubeVertices[7] = domain.domain[x+1][y+1][z+1];

                    int config_n = 0;
                    for(int i = 0; i < 8; i++)
                    {
                        config_n |= (unitCubeVertices[i] < isoLevel) << i;
                    }

                    if(config_n == 0 || config_n == 255)
                        continue;

                    // std::cout << x << " " << y << " " << z << "mid" << std::endl;

                    if (y == 0 && z == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[0], unitCubeVertices[1], 0, x, y, z, domain.size);
					if (z == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[2], unitCubeVertices[3], 0, x, y + 1, z, domain.size);
					if (y == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[4], unitCubeVertices[5], 0, x, y, z + 1, domain.size);
					addEdge(edgeIndexMap, mesh, unitCubeVertices[6], unitCubeVertices[7], 0, x, y + 1, z + 1, domain.size);

					if (x == 0 && z == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[0], unitCubeVertices[2], 1, x, y, z, domain.size);
					if (z == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[1], unitCubeVertices[3], 1,x + 1, y, z, domain.size);
					if (x == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[4], unitCubeVertices[6], 1, x, y, z + 1, domain.size);
					addEdge(edgeIndexMap, mesh, unitCubeVertices[5], unitCubeVertices[7], 1, x + 1, y, z + 1, domain.size);

					if (x == 0 && y == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[0], unitCubeVertices[4], 2, x, y, z, domain.size);
					if (y == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[1], unitCubeVertices[5], 2, x + 1, y, z, domain.size);
					if (x == 0)
						addEdge(edgeIndexMap, mesh, unitCubeVertices[2], unitCubeVertices[6], 2, x, y + 1, z, domain.size);
					addEdge(edgeIndexMap, mesh, unitCubeVertices[3], unitCubeVertices[7], 2, x + 1, y + 1, z, domain.size);

                    // std::cout << x << " " << y << " " << z << "bottom" << std::endl;

                    edgeIndices[0] = edgeIndexMap[index3DTo1D(x, y, z, domain.size)].x;
					edgeIndices[1] = edgeIndexMap[index3DTo1D(x, y + 1, z, domain.size)].x;
					edgeIndices[2] = edgeIndexMap[index3DTo1D(x, y, z + 1, domain.size)].x;
					edgeIndices[3] = edgeIndexMap[index3DTo1D(x, y + 1, z + 1, domain.size)].x;
					edgeIndices[4] = edgeIndexMap[index3DTo1D(x, y, z, domain.size)].y;
					edgeIndices[5] = edgeIndexMap[index3DTo1D(x + 1, y, z, domain.size)].y;
					edgeIndices[6] = edgeIndexMap[index3DTo1D(x, y, z + 1, domain.size)].y;
					edgeIndices[7] = edgeIndexMap[index3DTo1D(x + 1, y, z + 1, domain.size)].y;
					edgeIndices[8] = edgeIndexMap[index3DTo1D(x, y, z, domain.size)].z;
					edgeIndices[9] = edgeIndexMap[index3DTo1D(x + 1, y, z, domain.size)].z;
					edgeIndices[10] = edgeIndexMap[index3DTo1D(x, y + 1, z, domain.size)].z;
					edgeIndices[11] = edgeIndexMap[index3DTo1D(x + 1, y + 1, z, domain.size)].z;

                    unsigned long long int config = mcConfig[config_n];
                    int nTriangles = config & 0xF;
                    int nIndices = nTriangles * 3;
                    int offset = 4;
                    
                    for(int i = 0; i < nIndices; i++)
                    {
                        int edge = (config >> offset) & 0xF;
                        mesh.indices.push_back(edgeIndices[edge]);
                        offset += 4;
                    }

                    for(int i = 0; i < nTriangles; i++)
                    {
                        calculateNormal(mesh, i*3, i*3 + 1, i*3 + 2);
                    }
                }
            }
        }

        // for(int i = 0; i < mesh.normals.size(); i++)
        // {
        //     mesh.normals[i].normalize();
        // }

        delete[] edgeIndexMap;
    }
}


#endif