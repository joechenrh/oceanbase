// Copyright (c) 2021 Alibaba Inc. All Rights Reserved.
// Author:
//   renqing <sean.yyj@antgroup.com>

#ifndef SRC_SQL_ENGINE_EXPR_OB_EXPR_VALIDATE_PASSWORD_STRENGTH_H_
#define SRC_SQL_ENGINE_EXPR_OB_EXPR_VALIDATE_PASSWORD_STRENGTH_H_

#include "sql/engine/expr/ob_expr_operator.h"

namespace oceanbase {
namespace sql {

typedef int (*ObValidatePasswordFunc)(
    const common::ObString &password, const ObBasicSessionInfo &session, bool &passed);
class ObExprValidatePasswordStrength : public ObFuncExprOperator {
public:
  enum PasswordStrength {
    STRENGTH_WEAK = 0,
    STRENGTH_LESSWEAK,
    STRENGTH_LOW,
    STRENGTH_MEDIUM,
    STRENGTH_STRONG,
    STRENGTH_MAX,
  };
  explicit ObExprValidatePasswordStrength(common::ObIAllocator &alloc);
  virtual ~ObExprValidatePasswordStrength();
  virtual int calc_result_type1(ObExprResType &type, ObExprResType &type1, common::ObExprTypeCtx &type_ctx) const;
  virtual int calc_result1(common::ObObj &result, const common::ObObj &obj1, common::ObExprCtx &expr_ctx) const;
  virtual int cg_expr(ObExprCGCtx &op_cg_ctx, const ObRawExpr &raw_expr, ObExpr &rt_expr) const override;
  static int eval_password_strength(const ObExpr &expr, ObEvalCtx &ctx, ObDatum &res_datum);

private:
  static int calc_password_strength(const common::ObString &password, const ObBasicSessionInfo &session, int &strength);
  static int validate_password_lessweak(
      const common::ObString &password, const ObBasicSessionInfo &session, bool &passed);
  static int validate_password_low(const common::ObString &password, const ObBasicSessionInfo &session, bool &passed);
  static int validate_password_medium(
      const common::ObString &password, const ObBasicSessionInfo &session, bool &passed);
  static int validate_password_strong(
      const common::ObString &password, const ObBasicSessionInfo &session, bool &passed);
  static const int64_t VALID_PASSWORD_LENGTH_MIN = 4;
  static const int64_t PASSWORD_STRENGTH_MULTIPLIER = 25;
  static const ObValidatePasswordFunc validate_funcs_[STRENGTH_MAX];
  // disallow copy
  DISALLOW_COPY_AND_ASSIGN(ObExprValidatePasswordStrength);
};
}  // namespace sql
}  // namespace oceanbase

#endif /* SRC_SQL_ENGINE_EXPR_OB_EXPR_VALIDATE_PASSWORD_STRENGTH_H_ */
