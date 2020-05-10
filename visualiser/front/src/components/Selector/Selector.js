import React from "react";
import "./Selector.css";

const Selector = (props) => {
  return (
    <div>
      <label className="uppercase">{props.name}</label>
      <select
        type="text"
        name={props.name.split(" ").join("")}
        value={props.value}
        onChange={props.onChange}
      >
        {props.items.map((name, index) => (
          <option value={name} key={index}>
            {name}
          </option>
        ))}
      </select>
    </div>
  );
};

export default Selector;
