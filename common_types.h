#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H
#include <QString>
#include <QVector>
//          PriceZonesWithCategory-->
//                                    Caption;
//                                    Color;
//                                    IdPriceZone;
//                                    PriceCategory-->
//                                                    Caption;
//                                                    IdPriceCategory;
//                                                    Price;
//
//          Seat                  -->
//                                   Available;
//                                   IdSeat;
//                                   IsSeat;
//                                   Number;
//                                   NumberCaption;
//                                   PriceColor;
//                                   PriceZone;
//                                   Row;
//                                   RowCaption;

//==============================================================================

//==============================================================================

struct Seat
{
int Available;
QString IdSeat;
int IsSeat;
int Number;
QString NumberCaption;
QString PriceColor;
QString PriceZone;
int Row;
QString RowCaption;
            };

//==============================================================================

struct PriceCategory
{
QString Caption;
QString IdPriceCategory;
int Price;
};
struct PriceZonesWithCategory
{
    QString Caption;
    QString Color;
    QString IdPriceZone;
    QVector<PriceCategory> PriceCategory;
};

#endif // COMMON_TYPES_H
