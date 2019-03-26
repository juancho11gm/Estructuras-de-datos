#ifndef __GRAPH__H__
#define __GRAPH__H__

#include <map>
#include <string>
#include <vector>
#include <fstream>


template< class T, class C >
class Graph
{
public:
  typedef std::vector< T >                TVertices;
  typedef std::map< unsigned long, C >    TRow;
  typedef std::map< unsigned long, TRow > TMatrix;
  typedef std::vector< bool >             TMarks;

protected:
  struct DijkstraNode
  {
    unsigned long Vertex;
    unsigned long Parent;
    C Cost;
    bool operator<( const DijkstraNode& b ) const
    {
      return( b.Cost < this->Cost );
    }
  };

  struct PrimNode
  {
    unsigned long Orig;
    unsigned long Dest;
    C Cost;
    bool operator<( const PrimNode& b ) const
    {
      return( b.Cost < this->Cost );
    }
  };


public:
  Graph( );
  virtual ~Graph( );

  unsigned long AddVertex( const T& v );
  void SetArc( unsigned long i, unsigned long j, const C& c );

  unsigned long GetNumberOfVertices( ) const;
  const T& GetVertex( unsigned long i ) const;

  bool HasArc( unsigned long i, unsigned long j ) const;
  C& GetCost( unsigned long i, unsigned long j ) ;

  void PrintPlaneGraph( ) const;
  void PrintPreorderGraph( unsigned long i ) const;
  void PrintLevelsGraph( unsigned long i ) const;
  void PrintGraphAsPNG( const std::string& filename ) const;
  Graph< T, C > operator*( const Graph< T, C >& other );
  std::vector< std::vector<unsigned long> >Dijkstra( const unsigned long& start);
  std::vector< std::vector<unsigned long>  > Prim( const unsigned long& start);
  std::vector< unsigned long > FloydWarshall( const unsigned long& start, const unsigned long& end );
protected:
  void PrintPreorderGraph_Dummy( unsigned long i, TMarks& m ) const;

public:
  TVertices m_Vertices;
  TMatrix   m_Costs;
};

#include "Graph.hxx"

#endif // __GRAPH__H__

// eof - Graph.h
