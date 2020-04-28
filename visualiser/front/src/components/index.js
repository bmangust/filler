import React from "react";
import Field from "./Field/Field";

const updateField = (map) => {
  ReactDOM.render(<Field field={map} />, $("#react"));
};

export default updateField;
