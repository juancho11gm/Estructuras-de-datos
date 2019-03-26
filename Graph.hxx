#ifndef __GRAPH__HXX__
#define __GRAPH__HXX__

#include <cstdlib>
#include <queue>
#include <limits>
#include <sstream>
#include <algorithm>

#include <iostream>

// -------------------------------------------------------------------------
template< class T, class C >
Graph< T, C >::
Graph( )
{
}

// -------------------------------------------------------------------------
template< class T, class C >
Graph< T, C >::
~Graph( )
{
}

// -------------------------------------------------------------------------
template< class T, class C >
unsigned long Graph< T, C >::
AddVertex( const T& v )
{
  this->m_Vertices.push_back( v );
  return( this->m_Vertices.size( ) - 1 );
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
SetArc( unsigned long i, unsigned long j, const C& c )
{
  this->m_Costs[ i ][ j ] = c;
}

// -------------------------------------------------------------------------
template< class T, class C >
unsigned long Graph< T, C >::
GetNumberOfVertices( ) const
{
  return( this->m_Vertices.size( ) );
}

// -------------------------------------------------------------------------
template< class T, class C >
const T& Graph< T, C >::
GetVertex( unsigned long i ) const
{
  return( this->m_Vertices[ i ] );
}

// -------------------------------------------------------------------------
template< class T, class C >
bool Graph< T, C >::
HasArc( unsigned long i, unsigned long j ) const
{
  typename TMatrix::const_iterator rIt = this->m_Costs.find( i );
  if( rIt != this->m_Costs.end( ) )
    return( rIt->second.find( j ) != rIt->second.end( ) );
  return( false );
}

// -------------------------------------------------------------------------
template< class T, class C >
C& Graph< T, C >::
GetCost( unsigned long i, unsigned long j )
{
  static C inf_cost = std::numeric_limits< C >::max( );
  if( this->HasArc( i, j ) )
    return( this->m_Costs[ i ][ j ] );
  else
    return( inf_cost );
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
PrintPlaneGraph( ) const
{
  typename TVertices::const_iterator vIt = this->m_Vertices.begin( );
  for( ; vIt != this->m_Vertices.end( ); vIt++ )
    std::cout << *vIt << " ";
  std::cout << std::endl;
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
PrintPreorderGraph( unsigned long i ) const
{
  TMarks m( this->m_Vertices.size( ), false );
  this->PrintPreorderGraph_Dummy( i, m );
  std::cout << std::endl;
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
PrintLevelsGraph( unsigned long i ) const
{
  std::vector< bool > m( this->m_Vertices.size( ), false );
  std::queue< unsigned long > q;
  q.push( i );
  while( !q.empty( ) )
  {
    unsigned long n = q.front( );
    q.pop( );

    if( m[ n ] )
      continue;

    std::cout << this->m_Vertices[ n ] << " ";
    m[ n ] = true;

    typename TMatrix::const_iterator cIt = this->m_Costs.find( n );
    if( cIt != this->m_Costs.end( ) )
    {
      typename TRow::const_iterator rIt = cIt->second.begin( );
      for( ; rIt != cIt->second.end( ); rIt++ )
        q.push( rIt->first );

    } // fi

  } // elihw
  std::cout << std::endl;
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
PrintGraphAsPNG( const std::string& filename ) const
{
  std::stringstream str;
  str << "echo \"digraph G{";

  typename TMatrix::const_iterator cIt = this->m_Costs.begin( );
  for( ; cIt != this->m_Costs.end( ); cIt++ )
  {
    typename TRow::const_iterator rIt = cIt->second.begin( );
    for( ; rIt != cIt->second.end( ); rIt++ )
    {
      str << cIt->first << "->" << rIt->first << " ";
      str
        << cIt->first << " [label=\""
        << this->m_Vertices[ cIt->first ] << "\"]; ";
      str
        << rIt->first << " [label=\""
        << this->m_Vertices[ rIt->first ] << "\"]; ";

    } // rof

  } // rof

  str << "}\" | dot -Tpng > " << filename;
  std::system( str.str( ).c_str( ) );
}

// -------------------------------------------------------------------------
template< class T, class C >
Graph< T, C > Graph< T, C >::
operator*( const Graph< T, C >& other )
{
}

// -------------------------------------------------------------------------
template< class T, class C >
void Graph< T, C >::
PrintPreorderGraph_Dummy( unsigned long i, TMarks& m ) const
{
  if( m[ i ] )
    return;

  std::cout << this->m_Vertices[ i ] << " ";
  m[ i ] = true;

  typename TMatrix::const_iterator cIt = this->m_Costs.find( i );
  if( cIt != this->m_Costs.end( ) )
  {
    typename TRow::const_iterator rIt = cIt->second.begin( );
    for( ; rIt != cIt->second.end( ); rIt++ )
      this->PrintPreorderGraph_Dummy( rIt->first, m );

  } // fi
}

// --------------------------------------------------------------------------
template< class T, class C >
std::vector< std::vector< unsigned long > > Graph< T, C >::
Prim( const unsigned long& start )
{
  std::vector< std::vector< unsigned long > > r_paths;

  std::vector< bool > marks( this->m_Vertices.size( ), false );
  marks[ start ] = true;

  std::vector< unsigned long > tree( this->m_Vertices.size(), -1 );
  tree[ start ] = start;

  std::vector< PrimNode > queue;
  std::vector< PrimNode > temp;
  PrimNode node;
  bool added;

  // Fill min heap with all edges in graph
  typename TMatrix::const_iterator cIt = this->m_Costs.begin( );
  for( ; cIt != this->m_Costs.end( ); cIt++ )
  {
    typename TRow::const_iterator rIt = cIt->second.begin( );
    for( ; rIt != cIt->second.end( ); rIt++ )
    {
        PrimNode nnode;
        nnode.Orig = cIt->first;
        nnode.Dest = rIt->first;
        nnode.Cost = rIt->second;
        queue.push_back( nnode );
        std::push_heap( queue.begin( ), queue.end( ) );

    } // rof

  } // rof

  while ( std::count( marks.begin(), marks.end(), true ) != this->m_Vertices.size( ) )
  {
    added = false;

    while (!added)
    {
      std::pop_heap( queue.begin( ), queue.end( ) );
      node = queue.back( );
      queue.pop_back( );

      if ( marks[ node.Orig ] && !marks[ node.Dest ] )
      {
        tree[ node.Dest ] = node.Orig;
        marks [ node.Dest ] = true;
        added = true;

        while ( !temp.empty( ) )
        {
          queue.push_back( temp.back( ) );
          temp.pop_back( );
          std::push_heap( queue.begin( ), queue.end( ) );

        } // elihw

      }
      else
      {
        temp.push_back( node );

      } // fi

    } // elihw

  } // elihw

  for ( unsigned long i = 0; i < this->m_Vertices.size( ); i++ )
  {
    if ( i != start )
    {
      std::vector< unsigned long > path;
      unsigned long vIt = i;
      do
      {
        path.push_back( vIt );
        vIt = tree[ vIt ];

      } while( tree[ vIt ] != vIt && vIt != -1 );
      if( vIt != -1 )
        path.push_back( vIt );

      std::reverse( path.begin( ), path.end( ) );
      r_paths.push_back( path );

    } // fi

  } // rof

  return( r_paths );
}

// --------------------------------------------------------------------------
template< class T, class C >
std::vector< std::vector< unsigned long > > Graph< T, C >::
Dijkstra( const unsigned long& start )
{
  std::vector< std::vector< unsigned long > > r_paths;

  std::vector< bool > marks( this->m_Vertices.size( ), false );
  std::vector< unsigned long > tree( this->m_Vertices.size( ), -1 );
  std::vector< DijkstraNode > queue;

  DijkstraNode node;
  node.Vertex = start;
  node.Parent = start;
  node.Cost = C( 0 );

  queue.push_back( node );

  while( !queue.empty( ) )
  {
    std::pop_heap( queue.begin( ), queue.end( ) );
    node = queue.back( );
    queue.pop_back( );

    if( marks[ node.Vertex ] )
      continue;

    marks[ node.Vertex ] = true;
    tree[ node.Vertex ] = node.Parent;

    //if( node.Vertex == end )
    //  queue.clear( );
    //else
    {
      typename TMatrix::const_iterator mIt = this->m_Costs.find( node.Vertex );

      if( mIt != this->m_Costs.end( ) )
      {
        typename TRow::const_iterator rIt = mIt->second.begin( );
        for( ; rIt != mIt->second.end( ); ++rIt )
        {
          DijkstraNode nnode;
          nnode.Vertex = rIt->first;
          nnode.Parent = node.Vertex;
          nnode.Cost = node.Cost + rIt->second;
          queue.push_back( nnode );
          std::push_heap( queue.begin( ), queue.end( ) );

        } // rof

      } // fi

    } // fi

  } // elihw

  for ( unsigned long i = 0; i < this->m_Vertices.size( ); i++ )
  {
    if ( i != start )
    {
      std::vector< unsigned long > path;
      unsigned long vIt = i;
      do
      {
        path.push_back( vIt );
        vIt = tree[ vIt ];

      } while( tree[ vIt ] != vIt && vIt != -1 );
      if( vIt != -1 )
        path.push_back( vIt );

      std::reverse( path.begin( ), path.end( ) );
      r_paths.push_back( path );

    } // fi

  } // rof

  return( r_paths );
}

// --------------------------------------------------------------------------
template< class T, class C >
std::vector< unsigned long > Graph< T, C >::
FloydWarshall( const unsigned long& start, const unsigned long& end )
{
  typedef std::map< unsigned long, long >    TRowInt;
  typedef std::map< unsigned long, TRowInt > TMatrixInt;
  static C inf_cost = std::numeric_limits< C >::max( );

  TMatrix m_dist, m_dist_o;
  TMatrixInt m_pred, m_pred_o;

  // Fill distance and predecessors matrices
  for ( unsigned int i = 0; i < this->m_Vertices.size( ); ++i )
  {
    for ( unsigned int j = 0; j < this->m_Vertices.size( ); ++j )
    {
      if ( i == j )
      {
        m_dist[ i ][ j ] = 0;
        m_pred[ i ][ j ] = -1;

      }
      else
      {
        if( this->HasArc( i, j ) )
        {
          m_dist[ i ][ j ] = this->m_Costs[ i ][ j ];
          m_pred[ i ][ j ] = i;

        }
        else
        {
          m_dist[ i ][ j ] = inf_cost;
          m_pred[ i ][ j ] = -1;

        } // fi

      } // fi

    } // rof

  } // rof

  // Start algorithm
  for ( unsigned int k = 0; k < this->m_Vertices.size( ); ++k )
  {
    // copy actual matrices for modification
    m_dist_o = m_dist;
    m_pred_o = m_pred;

    for ( unsigned int i = 0; i < this->m_Vertices.size( ); ++i )
    {
      for ( unsigned int j = 0; j < this->m_Vertices.size( ); ++j )
      {
        if ( m_dist_o[ i ][ k ] + m_dist_o[ k ][ j ] < m_dist_o[ i ][ j ] )
        {
          m_dist[ i ][ j ] = m_dist_o[ i ][ k ] + m_dist_o[ k ][ j ];
          m_pred[ i ][ j ] = m_pred_o[ k ][ j ];

        } // fi

      } // rof

    } // rof

  } // rof

  // Build path from the final predecessors matrix
  std::vector< unsigned long > path;
  unsigned long iIt = start;
  unsigned long jIt = end;
  do
  {
    path.push_back( jIt );
    jIt = m_pred[ iIt ][ jIt ];

  } while( jIt != iIt && jIt != -1 );
  if( jIt != -1 )
    path.push_back( jIt );

  std::reverse( path.begin( ), path.end( ) );
  return( path );
}

#endif // __GRAPH__HXX__

// eof - Graph.hxx
