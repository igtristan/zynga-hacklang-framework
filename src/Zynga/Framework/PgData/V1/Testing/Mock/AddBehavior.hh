<?hh //strict

namespace Zynga\Framework\PgData\V1\Testing\Mock;

enum AddBehavior: int {
  Succeeds = 0;
  Fails = 1;
  ThrowsException = 2;
}
